#include <tdme/gui/elements/GUIGridController.h>

#include <algorithm>
#include <string>
#include <unordered_set>
#include <vector>

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
#include <tdme/gui/GUIParser.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTokenizer.h>
#include <tdme/utilities/StringTools.h>

using std::count;
using std::string;
using std::to_string;
using std::unordered_set;
using std::vector;

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
using tdme::gui::GUIParser;
using tdme::utilities::Exception;
using tdme::utilities::Integer;
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
	try {
		horizontalItems = Integer::parse(required_dynamic_cast<GUIElementNode*>(node)->getOptionValue("horizontal-items"));
	} catch (Exception &exception) {
		Console::println("GUIGridController::initialize(): options: horizontal-items: invalid value: " + required_dynamic_cast<GUIElementNode*>(node)->getOptionValue("horizontal-items"));
	}
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
	auto itemElementNodeController = gridItemElementNode->getController();
	for (auto i = 0; i < gridItemControllers.size(); i++) {
		if (gridItemControllers[i] == itemElementNodeController) return i;
	}
	return -1;
}

void GUIGridController::unselect()
{
	value.set(MutableString());
	auto itemIdx = getFocussedItemIdx();
	if (itemIdx == -1) return;
	gridItemControllers[itemIdx]->unselect();
}

void GUIGridController::select(int itemIdx) {
	if (itemIdx < 0 || itemIdx >= gridItemControllers.size()) return;
	if (multipleSelection == true) {
		for (auto gridItemController: gridItemControllers) gridItemController->unselect();
	}
	gridItemControllers[itemIdx]->select();
	value.reset();
	if (multipleSelection == true) value.append(VALUE_DELIMITER);
	value.append(required_dynamic_cast<GUIElementNode*>(gridItemControllers[itemIdx]->getNode())->getValue());
	if (multipleSelection == true) value.append(VALUE_DELIMITER);
}

void GUIGridController::select(GUIElementNode* gridItemElementNode) {
	auto itemIdx = getItemIdx(gridItemElementNode);
	if (itemIdx == -1) return;
	select(itemIdx);
}

void GUIGridController::unfocus()
{
	auto itemIdx = getFocussedItemIdx();
	if (itemIdx == -1) return;
	gridItemControllers[itemIdx]->unfocus();
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
	auto itemIdx = getItemIdx(gridItemElementNode);
	if (itemIdx == -1) return;
	focus(itemIdx);
}

void GUIGridController::selectCurrent()
{
	setValue(getValue());
}

void GUIGridController::focusNext()
{
	auto itemIdx = getFocussedItemIdx();
	if (itemIdx == -1) return;

	unfocus();

	auto disabledCount = 0;
	while (disabledCount < gridItemControllers.size()) {
		if (++itemIdx >= gridItemControllers.size()) itemIdx = gridItemControllers.size() - 1;
		if (gridItemControllers[itemIdx]->isDisabled() == false) break;
		disabledCount++;
	}
	if (disabledCount == gridItemControllers.size()) {
		itemIdx = -1;
		return;
	}

	focus(itemIdx);
}

void GUIGridController::focusPrevious()
{
	auto itemIdx = getFocussedItemIdx();
	if (itemIdx == -1) return;

	unfocus();

	auto disabledCount = 0;
	while (disabledCount < gridItemControllers.size()) {
		if (--itemIdx < 0) itemIdx = 0;
		if (gridItemControllers[itemIdx]->isDisabled() == false) break;
		disabledCount++;
	}
	if (disabledCount == gridItemControllers.size()) {
		itemIdx = -1;
		return;
	}

	focus(itemIdx);
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
	auto itemIdx = getItemIdx(gridItemElementNode);
	if (itemIdx == -1) return;
	toggle(itemIdx);
}

void GUIGridController::select()
{
	auto itemIdx = getFocussedItemIdx();
	if (itemIdx == -1) return;
	gridItemControllers[itemIdx]->select();
	gridItemControllers[itemIdx]->getNode()->scrollToNodeX(required_dynamic_cast<GUIParentNode*>(node));
	gridItemControllers[itemIdx]->getNode()->scrollToNodeY(required_dynamic_cast<GUIParentNode*>(node));
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
	// TODO: actually we should rebuild value to remove items that have not been found
	for (auto i = 0; i < gridItemControllers.size(); i++) {
		auto gridItemController = gridItemControllers[i];
		auto gridItemNode = required_dynamic_cast<GUIElementNode*>(gridItemController->getNode());
		auto itemValue = gridItemNode->getValue();
		if (gridItemController->isSelected() == true) gridItemController->unselect();
		if (gridItemController->isFocussed() == true) gridItemController->unfocus();
		if (valueSet.find(itemValue) != valueSet.end()) {
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
	// TODO: find a better way later maybe, this is working, but has some issues with adding nodes
	//	we need a <grid-layout> later for the following code
	if (onSubTreeChangeRun == true) return;
	//
	onSubTreeChangeRun = true;
	//
	auto unlayoutedParentNode = required_dynamic_cast<GUIParentNode*>(node->getScreenNode()->getNodeById(node->getId() + "_unlayouted"));
	if (unlayoutedParentNode->getSubNodesCount() == 0) return;
	//
	determineItems();
	//
	auto layoutedParentNode = required_dynamic_cast<GUIParentNode*>(node->getScreenNode()->getInnerNodeById(node->getId()));
	layoutedParentNode->clearSubNodes();
	auto gridItemIdx = 0;
	auto gridHorizontalLayoutIdx = 0;
	auto gridHorizontalLayoutId = node->getId() +"_hl_" + to_string(gridHorizontalLayoutIdx++);
	GUIParser::parse(layoutedParentNode, "<layout id=\"" + gridHorizontalLayoutId + "\" alignment=\"horizontal\" width=\"auto\"></layout>\n");
	//
	while (unlayoutedParentNode->getSubNodesCount() > 0) {
		required_dynamic_cast<GUIParentNode*>(node->getScreenNode()->getNodeById(gridHorizontalLayoutId))->moveSubNode(unlayoutedParentNode, 0);
		gridItemIdx++;
		if ((gridItemIdx % 2) == 0 && unlayoutedParentNode->getSubNodesCount() > 0) {
			gridHorizontalLayoutId = node->getId() +"_hl_" + to_string(gridHorizontalLayoutIdx++);
			GUIParser::parse(layoutedParentNode, "<layout id=\"" + gridHorizontalLayoutId + "\" alignment=\"horizontal\" width=\"auto\"></layout>\n");
		}
	}
	GUINode::dumpNode(layoutedParentNode);
	//
	onSubTreeChangeRun = false;
}
