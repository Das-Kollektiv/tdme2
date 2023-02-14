#include <tdme/gui/elements/GUIGridController.h>

#include <algorithm>
#include <unordered_set>

#include <tdme/tdme.h>
#include <tdme/gui/elements/GUIGridItemController.h>
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

using tdme::gui::elements::GUIGridController;
using tdme::gui::elements::GUIGridItemController;
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

string GUIGridController::CONDITION_DISABLED = "disabled";
string GUIGridController::CONDITION_ENABLED = "enabled";

GUIGridController::GUIGridController(GUINode* node)
	: GUIElementController(node)
{
	this->disabled = required_dynamic_cast<GUIElementNode*>(node)->isDisabled();
	this->multipleSelection = required_dynamic_cast<GUIElementNode*>(node)->hasOption("multiple");
	this->keyControl = false;
	this->focussedItemIdx = -1;
}

bool GUIGridController::isMultipleSelection() {
	return multipleSelection;
}

bool GUIGridController::isKeyControlDown() {
	return keyControl;
}

void GUIGridController::initialize()
{
	GUIElementController::initialize();
	value.reset();
	determineItems();
	for (auto gridItemController: gridItemControllers) {
		if (gridItemController->isSelected() == false) continue;
		if (multipleSelection == true) {
			if (value.empty() == true) {
				value.append(VALUE_DELIMITER);
			}
			value.append(required_dynamic_cast<GUIElementNode*>(gridItemController->getNode())->getValue());
			value.append(VALUE_DELIMITER);
		} else {
			value.set(required_dynamic_cast<GUIElementNode*>(gridItemController->getNode())->getValue());
		}
	}
	determineItems();
	selectCurrent();
}

void GUIGridController::dispose()
{
	GUIElementController::dispose();
}

void GUIGridController::postLayout()
{
}

int GUIGridController::getFocussedItemIdx()
{
	if (gridItemControllers.empty() == true) {
		focussedItemIdx = -1;
	} else
	if (focussedItemIdx == -1) {
		focussedItemIdx = 0;
	} else
	if (focussedItemIdx < 0) {
		focussedItemIdx = 0;
	} else
	if (focussedItemIdx >= gridItemControllers.size()) {
		focussedItemIdx = gridItemControllers.size() - 1;
	}
	return focussedItemIdx;
}

int GUIGridController::getItemIdx(GUIElementNode* gridItemElementNode) {
	auto optionElementNodeController = gridItemElementNode->getController();
	for (auto i = 0; i < gridItemControllers.size(); i++) {
		if (gridItemControllers[i] == optionElementNodeController) return i;
	}
	return -1;
}

void GUIGridController::unselect()
{
	value.set(MutableString());
	auto optionIdx = getFocussedItemIdx();
	if (optionIdx == -1) return;
	gridItemControllers[optionIdx]->unselect();
}

void GUIGridController::select(int optionIdx) {
	if (optionIdx < 0 || optionIdx >= gridItemControllers.size()) return;
	if (multipleSelection == true) {
		for (auto selectBoxOptionController: gridItemControllers) selectBoxOptionController->unselect();
	}
	gridItemControllers[optionIdx]->select();
	value.reset();
	if (multipleSelection == true) value.append(VALUE_DELIMITER);
	value.append(required_dynamic_cast<GUIElementNode*>(gridItemControllers[optionIdx]->getNode())->getValue());
	if (multipleSelection == true) value.append(VALUE_DELIMITER);
}

void GUIGridController::select(GUIElementNode* gridItemElementNode) {
	auto optionIdx = getItemIdx(gridItemElementNode);
	if (optionIdx == -1) return;
	select(optionIdx);
}

void GUIGridController::unfocus()
{
	auto optionIdx = getFocussedItemIdx();
	if (optionIdx == -1) return;
	gridItemControllers[optionIdx]->unfocus();
}

void GUIGridController::focus(int itemIdx)
{
	if (itemIdx < 0 || itemIdx >= gridItemControllers.size()) return;
	gridItemControllers[itemIdx]->focus();
	gridItemControllers[itemIdx]->getNode()->scrollToNodeX(required_dynamic_cast<GUIParentNode*>(node));
	gridItemControllers[itemIdx]->getNode()->scrollToNodeY(required_dynamic_cast<GUIParentNode*>(node));
	focussedItemIdx = itemIdx;
}

void GUIGridController::focus(GUIElementNode* gridItemElementNode)
{
	auto optionIdx = getItemIdx(gridItemElementNode);
	if (optionIdx == -1) return;
	focus(optionIdx);
}

void GUIGridController::selectCurrent()
{
	setValue(getValue());
}

void GUIGridController::focusNext()
{
	auto optionIdx = getFocussedItemIdx();
	if (optionIdx == -1) return;

	unfocus();

	auto disabledCount = 0;
	while (disabledCount < gridItemControllers.size()) {
		if (++optionIdx >= gridItemControllers.size()) optionIdx = gridItemControllers.size() - 1;
		if (gridItemControllers[optionIdx]->isDisabled() == false) break;
		disabledCount++;
	}
	if (disabledCount == gridItemControllers.size()) {
		optionIdx = -1;
		return;
	}

	focus(optionIdx);
}

void GUIGridController::focusPrevious()
{
	auto optionIdx = getFocussedItemIdx();
	if (optionIdx == -1) return;

	unfocus();

	auto disabledCount = 0;
	while (disabledCount < gridItemControllers.size()) {
		if (--optionIdx < 0) optionIdx = 0;
		if (gridItemControllers[optionIdx]->isDisabled() == false) break;
		disabledCount++;
	}
	if (disabledCount == gridItemControllers.size()) {
		optionIdx = -1;
		return;
	}

	focus(optionIdx);
}

void GUIGridController::toggle(int itemIdx)
{
	if (itemIdx < 0 || itemIdx >= gridItemControllers.size()) return;
	gridItemControllers[itemIdx]->toggle();
	gridItemControllers[itemIdx]->getNode()->scrollToNodeX(required_dynamic_cast<GUIParentNode*>(node));
	gridItemControllers[itemIdx]->getNode()->scrollToNodeY(required_dynamic_cast<GUIParentNode*>(node));
	string selectionValue;
	selectionValue+= VALUE_DELIMITER;
	selectionValue+= required_dynamic_cast<GUIElementNode*>(gridItemControllers[itemIdx]->getNode())->getValue();
	selectionValue+= VALUE_DELIMITER;
	if (gridItemControllers[itemIdx]->isSelected() == true) {
		value.append(value.getString().empty() == false?selectionValue.substr(1):selectionValue);
	} else {
		value.replace(selectionValue, "|");
		if (value.equals("|") == true) value.reset();
	}
}

void GUIGridController::toggle(GUIElementNode* gridItemElementNode)
{
	auto optionIdx = getItemIdx(gridItemElementNode);
	if (optionIdx == -1) return;
	toggle(optionIdx);
}

void GUIGridController::select()
{
	auto optionIdx = getFocussedItemIdx();
	if (optionIdx == -1) return;
	gridItemControllers[optionIdx]->select();
	gridItemControllers[optionIdx]->getNode()->scrollToNodeX(required_dynamic_cast<GUIParentNode*>(node));
	gridItemControllers[optionIdx]->getNode()->scrollToNodeY(required_dynamic_cast<GUIParentNode*>(node));
}

void GUIGridController::determineItems() {
	vector<GUINode*> childControllerNodes;
	//
	required_dynamic_cast<GUIParentNode*>(node)->getChildControllerNodes(childControllerNodes);
	//
	gridItemControllers.clear();
	for (auto i = 0; i < childControllerNodes.size(); i++) {
		auto childControllerNode = childControllerNodes[i];
		auto childController = childControllerNode->getController();
		auto gridItemController = dynamic_cast<GUIGridItemController*>(childController);
		if (gridItemController != nullptr) {
			gridItemControllers.push_back(gridItemController);
		}
	}
}

void GUIGridController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	GUIElementController::handleMouseEvent(node, event);
	auto disabled = required_dynamic_cast<GUIGridController*>(this->node->getController())->isDisabled();
	if (disabled == false && node == this->node && node->isEventBelongingToNode(event) && event->getButton() == MOUSE_BUTTON_LEFT) {
		if (event->getType() == GUIMouseEvent::MOUSEEVENT_PRESSED) {
			node->getScreenNode()->getGUI()->setFoccussedNode(required_dynamic_cast<GUIElementNode*>(node));
		}
	}
}

void GUIGridController::handleKeyboardEvent(GUIKeyboardEvent* event)
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
						select(getFocussedItemIdx());
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
						select(getFocussedItemIdx());
					}
				} else
				if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_RELEASED) {
					node->getScreenNode()->forwardChange(required_dynamic_cast<GUIElementNode*>(node));
				}
			}
			break;
		case GUIKeyboardEvent::KEYCODE_SPACE: {
				event->setProcessed(true);
				if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
					if (multipleSelection == true) {
						toggle(getFocussedItemIdx());
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

void GUIGridController::tick()
{
	GUIElementController::tick();
}

void GUIGridController::onFocusGained()
{
}

void GUIGridController::onFocusLost()
{
	keyControl = false;
}

bool GUIGridController::hasValue()
{
	return true;
}

const MutableString& GUIGridController::getValue()
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

void GUIGridController::setValue(const MutableString& value)
{
	unfocus();
	determineItems();
	unordered_set<string> valueSet;
	StringTokenizer valueTokenizer;
	valueTokenizer.tokenize(value.getString(), "|");
	while (valueTokenizer.hasMoreTokens()) {
		valueSet.insert(valueTokenizer.nextToken());
	}
	MutableString searchValue;
	GUIGridItemController* gridItemControllerLast = nullptr;
	// TODO: actually we should rebuild value to remove options that have not been found
	for (auto i = 0; i < gridItemControllers.size(); i++) {
		auto gridItemController = gridItemControllers[i];
		auto gridItemNode = required_dynamic_cast<GUIElementNode*>(gridItemController->getNode());
		auto optionValue = gridItemNode->getValue();
		if (gridItemController->isSelected() == true) gridItemController->unselect();
		if (gridItemController->isFocussed() == true) gridItemController->unfocus();
		if (valueSet.find(optionValue) != valueSet.end()) {
			if (multipleSelection == true) toggle(i);
			gridItemControllerLast = gridItemController;
		}
	}
	if (gridItemControllerLast != nullptr) {
		if (multipleSelection == false) select(required_dynamic_cast<GUIElementNode*>(gridItemControllerLast->getNode()));
		focus(required_dynamic_cast<GUIElementNode*>(gridItemControllerLast->getNode()));
		gridItemControllerLast->getNode()->scrollToNodeX(required_dynamic_cast<GUIParentNode*>(node));
		gridItemControllerLast->getNode()->scrollToNodeY(required_dynamic_cast<GUIParentNode*>(node));
	} else
	if (gridItemControllers.empty() == false) {
		auto gridItemController = gridItemControllers[0];
		auto gridItemNode = required_dynamic_cast<GUIElementNode*>(gridItemController->getNode());
		select(0);
		focus(0);
		gridItemNode->scrollToNodeX(required_dynamic_cast<GUIParentNode*>(node));
		gridItemNode->scrollToNodeY(required_dynamic_cast<GUIParentNode*>(node));
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

void GUIGridController::onSubTreeChange() {
	determineItems();
}
