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
#include <tdme/utilities/StringTools.h>

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
using tdme::utilities::StringTools;

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
}

void GUISelectBoxController::initialize()
{
	GUIElementController::initialize();
	value.reset();
	determineAllOptions();
	for (auto selectBoxOptionController: selectBoxOptionControllers) {
		if (selectBoxOptionController->isSelected() == false) continue;
		if (multipleSelection == true) {
			if (value.empty() == true) {
				value.append(VALUE_DELIMITER);
			}
			value.append(required_dynamic_cast<GUIElementNode*>(selectBoxOptionController->getNode())->getValue());
			value.append(VALUE_DELIMITER);
		} else {
			value.set(required_dynamic_cast<GUIElementNode*>(selectBoxOptionController->getNode())->getValue());
		}
	}
	determineExpandedOptions();
	selectCurrent();
}

void GUISelectBoxController::dispose()
{
	GUIElementController::dispose();
}

void GUISelectBoxController::postLayout()
{
}

int GUISelectBoxController::getFocussedOptionIdx()
{
	if (selectBoxOptionControllers.empty() == true) {
		focussedOptionIdx = -1;
	} else
	if (focussedOptionIdx == -1) {
		focussedOptionIdx = 0;
	} else
	if (focussedOptionIdx < 0) {
		focussedOptionIdx = 0;
	} else
	if (focussedOptionIdx >= selectBoxOptionControllers.size()) {
		focussedOptionIdx = selectBoxOptionControllers.size() - 1;
	}
	return focussedOptionIdx;
}

int GUISelectBoxController::getOptionIdx(GUIElementNode* optionElementNode) {
	auto optionElementNodeController = optionElementNode->getController();
	for (auto i = 0; i < selectBoxOptionControllers.size(); i++) {
		if (selectBoxOptionControllers[i] == optionElementNodeController) return i;
	}
	return -1;
}

void GUISelectBoxController::unselect()
{
	value.set(MutableString());
	auto optionIdx = getFocussedOptionIdx();
	if (optionIdx == -1) return;
	selectBoxOptionControllers[optionIdx]->unselect();
}

void GUISelectBoxController::select(int optionIdx) {
	if (optionIdx < 0 || optionIdx >= selectBoxOptionControllers.size()) return;
	if (multipleSelection == true) {
		for (auto selectBoxOptionController: selectBoxOptionControllers) selectBoxOptionController->unselect();
	}
	selectBoxOptionControllers[optionIdx]->select();
	value.reset();
	if (multipleSelection == true) value.append(VALUE_DELIMITER);
	value.append(required_dynamic_cast<GUIElementNode*>(selectBoxOptionControllers[optionIdx]->getNode())->getValue());
	if (multipleSelection == true) value.append(VALUE_DELIMITER);
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
	selectBoxOptionControllers[optionIdx]->unfocus();
}

void GUISelectBoxController::focus(int optionIdx)
{
	if (optionIdx < 0 || optionIdx >= selectBoxOptionControllers.size()) return;
	selectBoxOptionControllers[optionIdx]->focus();
	selectBoxOptionControllers[optionIdx]->getNode()->scrollToNodeX(required_dynamic_cast<GUIParentNode*>(node));
	selectBoxOptionControllers[optionIdx]->getNode()->scrollToNodeY(required_dynamic_cast<GUIParentNode*>(node));
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

	if (++optionIdx >= selectBoxOptionControllers.size()) optionIdx = selectBoxOptionControllers.size() - 1;

	focus(optionIdx);
}

void GUISelectBoxController::focusPrevious()
{
	auto optionIdx = getFocussedOptionIdx();
	if (optionIdx == -1) return;

	unfocus();

	if (--optionIdx < 0) optionIdx = 0;

	focus(optionIdx);
}

void GUISelectBoxController::toggle(int optionIdx)
{
	if (optionIdx < 0 || optionIdx >= selectBoxOptionControllers.size()) return;
	selectBoxOptionControllers[optionIdx]->toggle();
	selectBoxOptionControllers[optionIdx]->getNode()->scrollToNodeX(required_dynamic_cast<GUIParentNode*>(node));
	selectBoxOptionControllers[optionIdx]->getNode()->scrollToNodeY(required_dynamic_cast<GUIParentNode*>(node));
	string selectionValue;
	selectionValue+= VALUE_DELIMITER;
	selectionValue+= required_dynamic_cast<GUIElementNode*>(selectBoxOptionControllers[optionIdx]->getNode())->getValue();
	selectionValue+= VALUE_DELIMITER;
	if (selectBoxOptionControllers[optionIdx]->isSelected() == true) {
		value.append(value.getString().empty() == false?selectionValue.substr(1):selectionValue);
	} else {
		value.replace(selectionValue, "|");
		if (value.equals("|") == true) value.reset();
	}
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
	selectBoxOptionControllers[optionIdx]->select();
	selectBoxOptionControllers[optionIdx]->getNode()->scrollToNodeX(required_dynamic_cast<GUIParentNode*>(node));
	selectBoxOptionControllers[optionIdx]->getNode()->scrollToNodeY(required_dynamic_cast<GUIParentNode*>(node));
}

void GUISelectBoxController::toggleOpenState(int optionIdx) {
	if (optionIdx < 0 || optionIdx >= selectBoxOptionControllers.size()) return;

	auto selectBoxParentOptionController = dynamic_cast<GUISelectBoxParentOptionController*>(selectBoxOptionControllers[optionIdx]);
	if (selectBoxParentOptionController != nullptr) selectBoxParentOptionController->toggleExpandState();

	// TODO: this is a workaround, actually due to condition updates, the relayout should happen automatically
	node->getScreenNode()->layout(node);
}

void GUISelectBoxController::expand(int optionIdx) {
	if (optionIdx < 0 || optionIdx >= selectBoxOptionControllers.size()) return;

	auto selectBoxParentOptionController = dynamic_cast<GUISelectBoxParentOptionController*>(selectBoxOptionControllers[optionIdx]);
	if (selectBoxParentOptionController != nullptr) {
		if (selectBoxParentOptionController->isExpanded() == false) selectBoxParentOptionController->toggleExpandState();
	}

	// TODO: this is a workaround, actually due to condition updates, the relayout should happen automatically
	node->getScreenNode()->layout(node);
}

void GUISelectBoxController::collapse(int optionIdx) {
	if (optionIdx < 0 || optionIdx >= selectBoxOptionControllers.size()) return;

	auto selectBoxParentOptionController = dynamic_cast<GUISelectBoxParentOptionController*>(selectBoxOptionControllers[optionIdx]);
	if (selectBoxParentOptionController != nullptr) {
		if (selectBoxParentOptionController->isExpanded() == true) selectBoxParentOptionController->toggleExpandState();
	}

	// TODO: this is a workaround, actually due to condition updates, the relayout should happen automatically
	node->getScreenNode()->layout(node);
}

void GUISelectBoxController::toggleOpenState(GUIElementNode* optionElementNode) {
	auto optionIdx = getOptionIdx(optionElementNode);
	if (optionIdx == -1) return;

	toggleOpenState(optionIdx);

	determineExpandedOptions();
}

void GUISelectBoxController::determineAllOptions() {
	//
	required_dynamic_cast<GUIParentNode*>(node)->getChildControllerNodes(childControllerNodes);
	//
	selectBoxOptionControllers.clear();
	for (auto i = 0; i < childControllerNodes.size(); i++) {
		auto childControllerNode = childControllerNodes[i];
		auto childController = childControllerNode->getController();
		auto selectBoxOptionController = dynamic_cast<GUISelectBoxOptionController*>(childController);
		if (selectBoxOptionController != nullptr) {
			selectBoxOptionControllers.push_back(selectBoxOptionController);
		}
	}
}

void GUISelectBoxController::determineExpandedOptions() {
	//
	required_dynamic_cast<GUIParentNode*>(node)->getChildControllerNodes(childControllerNodes);
	//
	selectBoxOptionControllers.clear();
	for (auto i = 0; i < childControllerNodes.size(); i++) {
		auto childControllerNode = childControllerNodes[i];
		auto childController = childControllerNode->getController();
		auto selectBoxOptionController = dynamic_cast<GUISelectBoxOptionController*>(childController);
		if (selectBoxOptionController != nullptr && selectBoxOptionController->isHierarchyExpanded() == true) {
			selectBoxOptionControllers.push_back(selectBoxOptionController);
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
			event->setProcessed(true);
			if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
				expand(getFocussedOptionIdx());
				determineExpandedOptions();
			}
			break;
		case GUIKeyboardEvent::KEYCODE_LEFT: {
				event->setProcessed(true);
				if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
					collapse(getFocussedOptionIdx());
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
	unfocus();
	determineAllOptions();
	for (auto selectBoxOptionController: selectBoxOptionControllers) selectBoxOptionController->unselect();
	MutableString searchValue;
	GUISelectBoxOptionController* selectBoxOptionNodeControllerLast = nullptr;
	for (auto i = 0; i < selectBoxOptionControllers.size(); i++) {
		auto selectBoxOptionController = selectBoxOptionControllers[i];
		auto selectBoxOptionNode = required_dynamic_cast<GUIElementNode*>(selectBoxOptionController->getNode());
		searchValue.reset();
		if (multipleSelection == true) searchValue.append(VALUE_DELIMITER);
		searchValue.append(selectBoxOptionNode->getValue());
		if (multipleSelection == true) searchValue.append(VALUE_DELIMITER);
		if ((multipleSelection == true && value.indexOf(searchValue) != -1) || (multipleSelection == false && value.equals(searchValue) == true)) {
			selectBoxOptionController->expandHierarchy();
			if (multipleSelection == true) toggle(i);
			selectBoxOptionNodeControllerLast = selectBoxOptionController;
		}
	}
	determineExpandedOptions();
	if (selectBoxOptionNodeControllerLast != nullptr) {
		if (multipleSelection == false) select(required_dynamic_cast<GUIElementNode*>(selectBoxOptionNodeControllerLast->getNode()));
		focus(required_dynamic_cast<GUIElementNode*>(selectBoxOptionNodeControllerLast->getNode()));
		selectBoxOptionNodeControllerLast->getNode()->scrollToNodeX(required_dynamic_cast<GUIParentNode*>(node));
		selectBoxOptionNodeControllerLast->getNode()->scrollToNodeY(required_dynamic_cast<GUIParentNode*>(node));
	} else
	if (selectBoxOptionControllers.empty() == false) {
		auto selectBoxOptionController = selectBoxOptionControllers[0];
		auto selectBoxOptionNode = required_dynamic_cast<GUIElementNode*>(selectBoxOptionController->getNode());
		select(0);
		focus(0);
		selectBoxOptionNode->scrollToNodeX(required_dynamic_cast<GUIParentNode*>(node));
		selectBoxOptionNode->scrollToNodeY(required_dynamic_cast<GUIParentNode*>(node));
	}
	// TODO: this is a workaround, actually due to condition updates, the relayout should happen automatically
	node->getScreenNode()->layout(node);
}

void GUISelectBoxController::onSubTreeChange() {
	determineExpandedOptions();
}
