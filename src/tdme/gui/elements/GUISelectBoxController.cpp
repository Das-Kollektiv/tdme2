#include <tdme/gui/elements/GUISelectBoxController.h>

#include <algorithm>
#include <unordered_set>

#include <tdme/tdme.h>
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
#include <tdme/utilities/StringTokenizer.h>
#include <tdme/utilities/StringTools.h>


using std::count;
using std::unordered_set;

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
using tdme::utilities::StringTokenizer;
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

	auto disabledCount = 0;
	while (disabledCount < selectBoxOptionControllers.size()) {
		if (++optionIdx >= selectBoxOptionControllers.size()) optionIdx = selectBoxOptionControllers.size() - 1;
		if (selectBoxOptionControllers[optionIdx]->isDisabled() == false) break;
		disabledCount++;
	}
	if (disabledCount == selectBoxOptionControllers.size()) {
		optionIdx = -1;
		return;
	}

	focus(optionIdx);
}

void GUISelectBoxController::focusPrevious()
{
	auto optionIdx = getFocussedOptionIdx();
	if (optionIdx == -1) return;

	unfocus();

	auto disabledCount = 0;
	while (disabledCount < selectBoxOptionControllers.size()) {
		if (--optionIdx < 0) optionIdx = 0;
		if (selectBoxOptionControllers[optionIdx]->isDisabled() == false) break;
		disabledCount++;
	}
	if (disabledCount == selectBoxOptionControllers.size()) {
		optionIdx = -1;
		return;
	}

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
	node->getScreenNode()->invalidateLayout(node);
}

void GUISelectBoxController::expand(int optionIdx) {
	if (optionIdx < 0 || optionIdx >= selectBoxOptionControllers.size()) return;

	auto selectBoxParentOptionController = dynamic_cast<GUISelectBoxParentOptionController*>(selectBoxOptionControllers[optionIdx]);
	if (selectBoxParentOptionController != nullptr) {
		if (selectBoxParentOptionController->isExpanded() == false) selectBoxParentOptionController->toggleExpandState();
	}

	// TODO: this is a workaround, actually due to condition updates, the relayout should happen automatically
	node->getScreenNode()->invalidateLayout(node);
}

void GUISelectBoxController::collapse(int optionIdx) {
	if (optionIdx < 0 || optionIdx >= selectBoxOptionControllers.size()) return;

	auto selectBoxParentOptionController = dynamic_cast<GUISelectBoxParentOptionController*>(selectBoxOptionControllers[optionIdx]);
	if (selectBoxParentOptionController != nullptr) {
		if (selectBoxParentOptionController->isExpanded() == true) selectBoxParentOptionController->toggleExpandState();
	}

	// TODO: this is a workaround, actually due to condition updates, the relayout should happen automatically
	node->getScreenNode()->invalidateLayout(node);
}

void GUISelectBoxController::toggleOpenState(GUIElementNode* optionElementNode) {
	auto optionIdx = getOptionIdx(optionElementNode);
	if (optionIdx == -1) return;

	toggleOpenState(optionIdx);

	determineExpandedOptions();
}

void GUISelectBoxController::determineAllOptions() {
	vector<GUINode*> childControllerNodes;
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
	vector<GUINode*> childControllerNodes;
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
	if (focussedOptionIdx >= selectBoxOptionControllers.size()) focussedOptionIdx = selectBoxOptionControllers.size() - 1;
}

void GUISelectBoxController::determineParentOptions() {
	vector<GUINode*> childControllerNodes;
	//
	required_dynamic_cast<GUIParentNode*>(node)->getChildControllerNodes(childControllerNodes);
	//
	selectBoxOptionControllers.clear();
	for (auto i = 0; i < childControllerNodes.size(); i++) {
		auto childControllerNode = childControllerNodes[i];
		auto childController = childControllerNode->getController();
		auto selectBoxParentOptionController = dynamic_cast<GUISelectBoxParentOptionController*>(childController);
		if (selectBoxParentOptionController != nullptr) {
			selectBoxOptionControllers.push_back(selectBoxParentOptionController);
		}
	}
}

void GUISelectBoxController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	GUIElementController::handleMouseEvent(node, event);
	auto disabled = required_dynamic_cast<GUISelectBoxController*>(this->node->getController())->isDisabled();
	if (disabled == false && node == this->node && node->isEventBelongingToNode(event) && event->getButton() == MOUSE_BUTTON_LEFT) {
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
			if (event->getKeyCode() == KEYBOARD_KEYCODE_LEFT_CTRL) keyControl = isKeyDown;
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
					node->getScreenNode()->forwardChange(required_dynamic_cast<GUIElementNode*>(node));
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
					node->getScreenNode()->forwardChange(required_dynamic_cast<GUIElementNode*>(node));
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
					node->getScreenNode()->forwardChange(required_dynamic_cast<GUIElementNode*>(node));
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
	// check if single value
	if (multipleSelection == true &&
		count(value.getString().begin(), value.getString().end(), '|') == 2) {
		singleValue.set(StringTools::substring(value.getString(), 1, value.getString().size() - 1));
		return singleValue;
	}
	// nope, take multiple value
	return value;
}

void GUISelectBoxController::setValue(const MutableString& value)
{
	unfocus();
	determineAllOptions();
	unordered_set<string> valueSet;
	StringTokenizer valueTokenizer;
	valueTokenizer.tokenize(value.getString(), "|");
	while (valueTokenizer.hasMoreTokens()) {
		valueSet.insert(valueTokenizer.nextToken());
	}
	MutableString searchValue;
	GUISelectBoxOptionController* selectBoxOptionNodeControllerLast = nullptr;
	// TODO: actually we should rebuild value to remove options that have not been found
	for (auto i = 0; i < selectBoxOptionControllers.size(); i++) {
		auto selectBoxOptionController = selectBoxOptionControllers[i];
		auto selectBoxOptionNode = required_dynamic_cast<GUIElementNode*>(selectBoxOptionController->getNode());
		auto optionValue = selectBoxOptionNode->getValue();
		if (selectBoxOptionController->isSelected() == true) selectBoxOptionController->unselect();
		if (selectBoxOptionController->isFocussed() == true) selectBoxOptionController->unfocus();
		if (valueSet.find(optionValue) != valueSet.end()) {
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
	node->getScreenNode()->invalidateLayout(node);
	//
	this->value.reset();
	for (auto& valueSetValue: valueSet) {
		this->value.append(VALUE_DELIMITER);
		this->value.append(valueSetValue);
	}
	if (valueSet.empty() == false) this->value.append(VALUE_DELIMITER);
}

void GUISelectBoxController::onSubTreeChange() {
	determineExpandedOptions();
}

void GUISelectBoxController::determineExpandedParentOptionValues(vector<string>& expandedParentOptionValues) {
	expandedParentOptionValues.clear();
	determineParentOptions();
	for (auto selectBoxParentOptionController: selectBoxOptionControllers) {
		if (required_dynamic_cast<GUISelectBoxParentOptionController*>(selectBoxParentOptionController)->isExpanded() == true) {
			expandedParentOptionValues.push_back(required_dynamic_cast<GUIElementNode*>(selectBoxParentOptionController->getNode())->getValue());
		}
	}
	determineExpandedOptions();
}

void GUISelectBoxController::expandParentOptionsByValues(const vector<string>& expandedParentOptionValues) {
	determineParentOptions();
	for (auto& expandedParentOptionValue: expandedParentOptionValues) {
		for (auto selectBoxParentOptionController: selectBoxOptionControllers) {
			if (expandedParentOptionValue == required_dynamic_cast<GUIElementNode*>(selectBoxParentOptionController->getNode())->getValue()) {
				auto parentOptionNodeController = required_dynamic_cast<GUISelectBoxParentOptionController*>(selectBoxParentOptionController);
				if (parentOptionNodeController->isExpanded() == false) parentOptionNodeController->toggleExpandState();
			}
		}
	}
	determineExpandedOptions();
	// TODO: this is a workaround, actually due to condition updates, the relayout should happen automatically
	node->getScreenNode()->invalidateLayout(node);
}
