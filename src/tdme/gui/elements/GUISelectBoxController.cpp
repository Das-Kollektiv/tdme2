#include <tdme/gui/elements/GUISelectBoxController.h>

#include <tdme/gui/elements/GUISelectBoxOptionController.h>
#include <tdme/gui/elements/GUISelectBoxParentOptionController.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIElementController.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/utilities/MutableString.h>

using tdme::gui::elements::GUISelectBoxController;
using tdme::gui::elements::GUISelectBoxOptionController;
using tdme::gui::elements::GUISelectBoxParentOptionController;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementController;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUI;
using tdme::utilities::MutableString;

constexpr char GUISelectBoxController::VALUE_DELIMITER;

string GUISelectBoxController::CONDITION_DISABLED = "disabled";
string GUISelectBoxController::CONDITION_ENABLED = "enabled";

GUISelectBoxController::GUISelectBoxController(GUINode* node)
	: GUIElementController(node)
{
	this->disabled = required_dynamic_cast<GUIElementNode*>(node)->isDisabled();
	this->multipleSelection = required_dynamic_cast<GUIElementNode*>(node)->hasOption("multiple");
	this->keyControl = false;
	this->focussedOptionIdx = -1;
}

bool GUISelectBoxController::isMultipleSelection() {
	return multipleSelection;
}

bool GUISelectBoxController::isKeyControlDown() {
	return keyControl;
}

bool GUISelectBoxController::isDisabled()
{
	return disabled;
}

void GUISelectBoxController::setDisabled(bool disabled)
{
	auto& nodeConditions = required_dynamic_cast<GUIElementNode*>(node)->getActiveConditions();
	nodeConditions.remove(this->disabled == true?CONDITION_DISABLED:CONDITION_ENABLED);
	this->disabled = disabled;
	nodeConditions.add(this->disabled == true ?CONDITION_DISABLED:CONDITION_ENABLED);
	selectCurrent();
}

void GUISelectBoxController::initialize()
{
	if (getFocussedOptionIdx() == -1) {
		auto value = getValue();
		setValue(value);
	}
	GUIElementController::initialize();
}

void GUISelectBoxController::dispose()
{
	GUIElementController::dispose();
}

void GUISelectBoxController::postLayout()
{
	// TODO: a.drewke, maybe we should have a better method for this, like onPostChildrenChange or something
	determineExpandedOptions();
}

int GUISelectBoxController::getFocussedOptionIdx()
{
	if (focussedOptionIdx != -1 && (focussedOptionIdx < 0 || focussedOptionIdx >= selectBoxMultipleOptionControllers.size())) {
		focussedOptionIdx = -1;
	}
	return focussedOptionIdx;
}

int GUISelectBoxController::getOptionIdx(GUIElementNode* optionElementNode) {
	auto optionElementNodeController = optionElementNode->getController();
	for (auto i = 0; i < selectBoxMultipleOptionControllers.size(); i++) {
		if (selectBoxMultipleOptionControllers[i] == optionElementNodeController) return i;
	}
	return -1;
}

void GUISelectBoxController::unselect()
{
	value.set(MutableString());
	auto optionIdx = getFocussedOptionIdx();
	if (optionIdx == -1) return;
	selectBoxMultipleOptionControllers[optionIdx]->unselect();
}

void GUISelectBoxController::select(int optionIdx) {
	if (optionIdx < 0 || optionIdx >= selectBoxMultipleOptionControllers.size()) return;
	selectBoxMultipleOptionControllers[optionIdx]->select();
	value.set(required_dynamic_cast<GUIElementNode*>(selectBoxMultipleOptionControllers[optionIdx]->getNode())->getValue());
}

void GUISelectBoxController::select(GUIElementNode* optionElementNode) {
	auto optionIdx = getOptionIdx(optionElementNode);
	if (optionIdx == -1) return;
	select(optionIdx);
}

void GUISelectBoxController::unfocus()
{
	auto optionIdx = getFocussedOptionIdx();
	if (optionIdx == -1) return;
	selectBoxMultipleOptionControllers[optionIdx]->unfocus();
}

void GUISelectBoxController::focus(int optionIdx)
{
	if (optionIdx < 0 || optionIdx >= selectBoxMultipleOptionControllers.size()) return;
	selectBoxMultipleOptionControllers[optionIdx]->focus();
	selectBoxMultipleOptionControllers[optionIdx]->getNode()->scrollToNodeX(required_dynamic_cast<GUIParentNode*>(node));
	selectBoxMultipleOptionControllers[optionIdx]->getNode()->scrollToNodeY(required_dynamic_cast<GUIParentNode*>(node));
	focussedOptionIdx = optionIdx;
}

void GUISelectBoxController::focus(GUIElementNode* optionElementNode)
{
	auto optionIdx = getOptionIdx(optionElementNode);
	if (optionIdx == -1) return;
	focus(optionIdx);
}

void GUISelectBoxController::selectCurrent()
{
	setValue(getValue());
}

void GUISelectBoxController::focusNext()
{
	auto optionIdx = getFocussedOptionIdx();
	if (optionIdx == -1) return;

	unfocus();

	optionIdx = (optionIdx + 1) % selectBoxMultipleOptionControllers.size();
	if (optionIdx < 0)
		optionIdx += selectBoxMultipleOptionControllers.size();

	focus(optionIdx);
}

void GUISelectBoxController::focusPrevious()
{
	auto optionIdx = getFocussedOptionIdx();
	if (optionIdx == -1) return;

	unfocus();

	optionIdx = (optionIdx - 1) % static_cast<int>(selectBoxMultipleOptionControllers.size());
	if (optionIdx < 0)
		optionIdx += selectBoxMultipleOptionControllers.size();

	focus(optionIdx);
}

void GUISelectBoxController::toggle(int optionIdx)
{
	if (optionIdx < 0 || optionIdx >= selectBoxMultipleOptionControllers.size()) return;
	selectBoxMultipleOptionControllers[optionIdx]->toggle();
	selectBoxMultipleOptionControllers[optionIdx]->getNode()->scrollToNodeX(required_dynamic_cast<GUIParentNode*>(node));
	selectBoxMultipleOptionControllers[optionIdx]->getNode()->scrollToNodeY(required_dynamic_cast<GUIParentNode*>(node));
}

void GUISelectBoxController::toggle(GUIElementNode* optionElementNode)
{
	auto optionIdx = getOptionIdx(optionElementNode);
	if (optionIdx == -1) return;
	toggle(optionIdx);
}

void GUISelectBoxController::select()
{
	auto optionIdx = getFocussedOptionIdx();
	if (optionIdx == -1) return;
	selectBoxMultipleOptionControllers[optionIdx]->select();
	selectBoxMultipleOptionControllers[optionIdx]->getNode()->scrollToNodeX(required_dynamic_cast<GUIParentNode*>(node));
	selectBoxMultipleOptionControllers[optionIdx]->getNode()->scrollToNodeY(required_dynamic_cast<GUIParentNode*>(node));
}

void GUISelectBoxController::toggleOpenState() {
	auto optionIdx = getFocussedOptionIdx();
	if (optionIdx == -1) return;

	auto selectBoxMultipleParentOptionController = dynamic_cast<GUISelectBoxParentOptionController*>(selectBoxMultipleOptionControllers[optionIdx]);
	if (selectBoxMultipleParentOptionController != nullptr) selectBoxMultipleParentOptionController->toggleOpenState();
}

void GUISelectBoxController::determineExpandedOptions() {
	//
	required_dynamic_cast<GUIParentNode*>(node)->getChildControllerNodes(childControllerNodes);
	//
	selectBoxMultipleOptionControllers.clear();
	for (auto i = 0; i < childControllerNodes.size(); i++) {
		auto childControllerNode = childControllerNodes[i];
		auto childController = childControllerNode->getController();
		auto selectBoxMultipleOptionController = dynamic_cast<GUISelectBoxOptionController*>(childController);
		if (selectBoxMultipleOptionController != nullptr && selectBoxMultipleOptionController->isCollapsed() == false) {
			selectBoxMultipleOptionControllers.push_back(selectBoxMultipleOptionController);
		}
	}
}

void GUISelectBoxController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	GUIElementController::handleMouseEvent(node, event);
	auto disabled = required_dynamic_cast<GUISelectBoxController*>(this->node->getController())->isDisabled();
	if (disabled == false && node == this->node && node->isEventBelongingToNode(event) && event->getButton() == MOUSE_BUTTON_LEFT) {
		event->setProcessed(true);
		if (event->getType() == GUIMouseEvent::MOUSEEVENT_PRESSED) {
			node->getScreenNode()->getGUI()->setFoccussedNode(required_dynamic_cast<GUIElementNode*>(node));
		}
	}
}

void GUISelectBoxController::handleKeyboardEvent(GUIKeyboardEvent* event)
{
	GUIElementController::handleKeyboardEvent(event);
	if (disabled == false) {
		if (event->getType() != GUIKeyboardEvent::KEYBOARDEVENT_KEY_TYPED) {
			auto isKeyDown = event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED;
			#if defined(GLFW3) || defined(VUKAN)
				if (event->getKeyCode() == KEYBOARD_KEYCODE_LEFT_CTRL) keyControl = isKeyDown;
			#else
				keyControl = event->isControlDown();
			#endif
		}

		switch (event->getKeyCode()) {
		case GUIKeyboardEvent::KEYCODE_UP: {
				event->setProcessed(true);
				if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
					if (multipleSelection == false) {
						unselect();
					}
					focusPrevious();
					if (multipleSelection == false) {
						select(getFocussedOptionIdx());
					}
				} else
				if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_RELEASED) {
					node->getScreenNode()->delegateValueChanged(required_dynamic_cast<GUIElementNode*>(node));
				}
			}
			break;
		case GUIKeyboardEvent::KEYCODE_DOWN: {
				event->setProcessed(true);
				if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
					if (multipleSelection == false) {
						unselect();
					}
					focusNext();
					if (multipleSelection == false) {
						select(getFocussedOptionIdx());
					}
				} else
				if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_RELEASED) {
					node->getScreenNode()->delegateValueChanged(required_dynamic_cast<GUIElementNode*>(node));
				}
			}
			break;
		case GUIKeyboardEvent::KEYCODE_RIGHT:
		case GUIKeyboardEvent::KEYCODE_LEFT: {
				event->setProcessed(true);
				if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
					toggleOpenState();
					determineExpandedOptions();
				}
			}
			break;
		case GUIKeyboardEvent::KEYCODE_SPACE: {
				event->setProcessed(true);
				if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
					if (multipleSelection == true) {
						toggle(getFocussedOptionIdx());
					}
				} else
				if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_RELEASED) {
					node->getScreenNode()->delegateValueChanged(required_dynamic_cast<GUIElementNode*>(node));
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
	keyControl = false;
}

bool GUISelectBoxController::hasValue()
{
	return true;
}

const MutableString& GUISelectBoxController::getValue()
{
	return value;
}

void GUISelectBoxController::setValue(const MutableString& value)
{
	unselect();
	unfocus();
	MutableString searchValue;
	int selectBoxOptionNodeLastIdx = -1;
	for (auto i = 0; i < selectBoxMultipleOptionControllers.size(); i++) {
		auto selectBoxOptionController = selectBoxMultipleOptionControllers[i];
		auto selectBoxOptionNode = required_dynamic_cast<GUIElementNode*>(selectBoxOptionController->getNode());
		searchValue.reset();
		if (multipleSelection == true) searchValue.append(VALUE_DELIMITER);
		searchValue.append(selectBoxOptionNode->getValue());
		if (multipleSelection == true) searchValue.append(VALUE_DELIMITER);
		if (value.indexOf(searchValue) != -1) {
			selectBoxOptionController->select();
			selectBoxOptionNode->scrollToNodeX(required_dynamic_cast<GUIParentNode*>(node));
			selectBoxOptionNode->scrollToNodeY(required_dynamic_cast<GUIParentNode*>(node));
			selectBoxOptionNodeLastIdx = i;
		}
	}
	if (selectBoxOptionNodeLastIdx != -1) focus(selectBoxOptionNodeLastIdx);
}
