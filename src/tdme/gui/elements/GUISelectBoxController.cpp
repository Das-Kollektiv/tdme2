#include <tdme/gui/elements/GUISelectBoxController.h>

#include <tdme/gui/GUI.h>
#include <tdme/gui/elements/GUISelectBoxOptionController.h>
#include <tdme/gui/events/GUIKeyboardEvent_Type.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent_Type.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIElementController.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/utils/MutableString.h>

using tdme::gui::elements::GUISelectBoxController;
using tdme::gui::GUI;
using tdme::gui::elements::GUISelectBoxOptionController;
using tdme::gui::events::GUIKeyboardEvent_Type;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent_Type;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementController;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::utils::MutableString;

string GUISelectBoxController::CONDITION_DISABLED = "disabled";
string GUISelectBoxController::CONDITION_ENABLED = "enabled";

GUISelectBoxController::GUISelectBoxController(GUINode* node) 
	: GUIElementController(node)
{
	init();
	this->disabled = (dynamic_cast< GUIElementNode* >(node))->isDisabled();
}

void GUISelectBoxController::init()
{
}

bool GUISelectBoxController::isDisabled()
{
	return disabled;
}

void GUISelectBoxController::setDisabled(bool disabled)
{
	auto& nodeConditions = (dynamic_cast< GUIElementNode* >(node))->getActiveConditions();
	nodeConditions.remove(this->disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
	this->disabled = disabled;
	nodeConditions.add(this->disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
	selectCurrent();
}

void GUISelectBoxController::initialize()
{
	GUIElementController::initialize();
}

void GUISelectBoxController::dispose()
{
	GUIElementController::dispose();
}

void GUISelectBoxController::postLayout()
{
}

void GUISelectBoxController::unselect()
{
	(dynamic_cast< GUIParentNode* >(node))->getChildControllerNodes(childControllerNodes);
	for (auto i = 0; i < childControllerNodes.size(); i++) {
		auto childControllerNode = childControllerNodes[i];
		auto childController = childControllerNode->getController();
		if (dynamic_cast< GUISelectBoxOptionController* >(childController) != nullptr) {
			(dynamic_cast< GUISelectBoxOptionController* >(childController))->unselect();
		}
	}
}

void GUISelectBoxController::determineSelectBoxOptionControllers()
{
	selectBoxOptionControllers.clear();
	(dynamic_cast< GUIParentNode* >(node))->getChildControllerNodes(childControllerNodes);
	for (auto i = 0; i < childControllerNodes.size(); i++) {
		auto childControllerNode = childControllerNodes[i];
		auto childController = childControllerNode->getController();
		if (dynamic_cast< GUISelectBoxOptionController* >(childController) != nullptr) {
			selectBoxOptionControllers.push_back(dynamic_cast< GUISelectBoxOptionController* >(childController));
		}
	}
}

int32_t GUISelectBoxController::getSelectedOptionIdx()
{
	auto selectBoxOptionControllerIdx = -1;
	for (auto i = 0; i < selectBoxOptionControllers.size(); i++) {
		auto selectBoxOptionController = selectBoxOptionControllers[i];
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

	selectBoxOptionControllers[selectBoxOptionControllerIdx]->select();
	selectBoxOptionControllers[selectBoxOptionControllerIdx]->getNode()->scrollToNodeX(dynamic_cast< GUIParentNode* >(node));
	selectBoxOptionControllers[selectBoxOptionControllerIdx]->getNode()->scrollToNodeY(dynamic_cast< GUIParentNode* >(node));
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

	selectBoxOptionControllers[selectBoxOptionControllerIdx]->select();
	selectBoxOptionControllers[selectBoxOptionControllerIdx]->getNode()->scrollToNodeX(dynamic_cast< GUIParentNode* >(node));
	selectBoxOptionControllers[selectBoxOptionControllerIdx]->getNode()->scrollToNodeY(dynamic_cast< GUIParentNode* >(node));
}

void GUISelectBoxController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	GUIElementController::handleMouseEvent(node, event);
	auto disabled = (dynamic_cast< GUISelectBoxController* >(this->node->getController()))->isDisabled();
	if (disabled == false && node == this->node && node->isEventBelongingToNode(event) && event->getButton() == 1) {
		event->setProcessed(true);
		if (event->getType() == GUIMouseEvent_Type::MOUSEEVENT_PRESSED) {
			node->getScreenNode()->getGUI()->setFoccussedNode(dynamic_cast< GUIElementNode* >(node));
		}
	}
}

void GUISelectBoxController::handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event)
{
	GUIElementController::handleKeyboardEvent(node, event);
	if (disabled == false && node == this->node) {
		switch (event->getKeyCode()) {
		case GUIKeyboardEvent::KEYCODE_UP: {
				event->setProcessed(true);
				if (event->getType() == GUIKeyboardEvent_Type::KEYBOARDEVENT_KEY_PRESSED) {
					selectPrevious();
					node->getScreenNode()->delegateValueChanged(dynamic_cast< GUIElementNode* >(node));
				}
			}
			break;
		case GUIKeyboardEvent::KEYCODE_DOWN: {
				event->setProcessed(true);
				if (event->getType() == GUIKeyboardEvent_Type::KEYBOARDEVENT_KEY_PRESSED) {
					selectNext();
					node->getScreenNode()->delegateValueChanged(dynamic_cast< GUIElementNode* >(node));
				}
			}
			break;
		}

	}
}

void GUISelectBoxController::tick()
{
	GUIElementController::tick();
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

const MutableString& GUISelectBoxController::getValue()
{
	value.reset();
	determineSelectBoxOptionControllers();
	for (auto i = 0; i < selectBoxOptionControllers.size(); i++) {
		auto selectBoxOptionController = selectBoxOptionControllers[i];
		if (selectBoxOptionController->isSelected() == true) {
			value.append((dynamic_cast< GUIElementNode* >(selectBoxOptionController->getNode()))->getValue());
		}
	}
	return value;
}

void GUISelectBoxController::setValue(const MutableString& value)
{
	determineSelectBoxOptionControllers();
	unselect();
	for (auto i = 0; i < selectBoxOptionControllers.size(); i++) {
		auto selectBoxOptionController = selectBoxOptionControllers[i];
		auto selectBoxOptionNode = dynamic_cast< GUIElementNode* >(selectBoxOptionController->getNode());
		if (value.equals(selectBoxOptionNode->getValue()) == true) {
			selectBoxOptionController->select();
			selectBoxOptionNode->scrollToNodeX(dynamic_cast< GUIParentNode* >(node));
			selectBoxOptionNode->scrollToNodeY(dynamic_cast< GUIParentNode* >(node));
			break;
		}
	}
}
