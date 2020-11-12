#include <tdme/gui/elements/GUIMenuHeaderItemController.h>

#include <tdme/gui/GUI.h>
#include <tdme/gui/elements/GUIMenuHeaderItemController.h>
#include <tdme/gui/elements/GUIMenuItemController.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIElementController.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

using tdme::gui::elements::GUIMenuHeaderItemController;
using tdme::gui::GUI;
using tdme::gui::elements::GUIMenuItemController;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementController;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::utilities::Console;
using tdme::utilities::MutableString;
using tdme::utilities::StringTools;

string GUIMenuHeaderItemController::CONDITION_DISABLED = "disabled";
string GUIMenuHeaderItemController::CONDITION_ENABLED = "enabled";
string GUIMenuHeaderItemController::CONDITION_OPENED = "opened";
string GUIMenuHeaderItemController::CONDITION_CLOSED = "closed";
string GUIMenuHeaderItemController::CONDITION_SELECTED = "selected";
string GUIMenuHeaderItemController::CONDITION_UNSELECTED = "unselected";


GUIMenuHeaderItemController::GUIMenuHeaderItemController(GUINode* node)
	: GUIElementController(node)
{
	init();
	this->disabled = (dynamic_cast< GUIElementNode* >(node))->isDisabled();
	this->selected = (dynamic_cast< GUIElementNode* >(node))->isSelected();
}

void GUIMenuHeaderItemController::init()
{
	open = false;
}

bool GUIMenuHeaderItemController::isDisabled()
{
	return disabled;
}

void GUIMenuHeaderItemController::setDisabled(bool disabled)
{
	if (itemNode == nullptr) {
		this->disabled = disabled;
		return;
	}
	auto& nodeConditions = (dynamic_cast<GUIElementNode*>(itemNode))->getActiveConditions();
	nodeConditions.remove(this->disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
	this->disabled = disabled;
	nodeConditions.add(this->disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
}

bool GUIMenuHeaderItemController::isSelected()
{
	return selected;
}

void GUIMenuHeaderItemController::select()
{
	auto& nodeConditions = (dynamic_cast<GUIElementNode*>(itemNode))->getActiveConditions();
	nodeConditions.remove(this->selected == true ? CONDITION_SELECTED : CONDITION_UNSELECTED);
	this->selected = true;
	nodeConditions.add(this->selected == true ? CONDITION_SELECTED : CONDITION_UNSELECTED);
}

void GUIMenuHeaderItemController::unselect()
{
	auto& nodeConditions = (dynamic_cast<GUIElementNode*>(itemNode))->getActiveConditions();
	nodeConditions.remove(this->selected == true ? CONDITION_SELECTED : CONDITION_UNSELECTED);
	this->selected = false;
	nodeConditions.add(this->selected == true ? CONDITION_SELECTED : CONDITION_UNSELECTED);
}

void GUIMenuHeaderItemController::initialize()
{
	(dynamic_cast< GUIElementNode* >(node))->getActiveConditions().add(open == true ? CONDITION_OPENED : CONDITION_CLOSED);

	//
	GUIElementController::initialize();

	//
	this->itemNode = node->getScreenNode()->getNodeById(node->getId() + "_item");
	setDisabled(this->disabled);
	if (this->selected == true) select(); else unselect();
}

void GUIMenuHeaderItemController::dispose()
{
	GUIElementController::dispose();
}

void GUIMenuHeaderItemController::postLayout()
{
}

bool GUIMenuHeaderItemController::isOpen()
{
	return open;
}

void GUIMenuHeaderItemController::toggleOpenState()
{
	(dynamic_cast<GUIElementNode*>(node))->getActiveConditions().remove(open == true?CONDITION_OPENED:CONDITION_CLOSED);
	open = open == true ? false : true;
	(dynamic_cast<GUIElementNode*>(node))->getActiveConditions().add(open == true?CONDITION_OPENED:CONDITION_CLOSED);
	if (open == true) select(); else unselect();
}

void GUIMenuHeaderItemController::determineMenuItemControllers()
{
	menuItemControllers.clear();
	(dynamic_cast< GUIParentNode* >(node))->getChildControllerNodes(childControllerNodes);
	for (auto i = 0; i < childControllerNodes.size(); i++) {
		auto childControllerNode = childControllerNodes[i];
		auto childController = childControllerNode->getController();
		if (dynamic_cast<GUIMenuItemController*>(childController) != nullptr) {
			menuItemControllers.push_back(dynamic_cast<GUIMenuItemController*>(childController));
		}
	}
}

int32_t GUIMenuHeaderItemController::getSelectedMenuItemControllerIdx()
{
	auto selectedMenuItemControllerIdx = 0;
	for (auto i = 0; i < menuItemControllers.size(); i++) {
		auto selectBoxOptionController = menuItemControllers[i];
		if (selectBoxOptionController->isSelected() == true) {
			selectedMenuItemControllerIdx = i;
			break;
		}
	}
	return selectedMenuItemControllerIdx;
}

void GUIMenuHeaderItemController::selectNext()
{
	determineMenuItemControllers();
	auto selectedMenuItemControllerIdx = getSelectedMenuItemControllerIdx();
	if (menuItemControllers.size() == 0) return;

	selectedMenuItemControllerIdx = (selectedMenuItemControllerIdx + 1) % menuItemControllers.size();
	if (selectedMenuItemControllerIdx < 0)
		selectedMenuItemControllerIdx += menuItemControllers.size();

	for (auto menuItemController: menuItemControllers) menuItemController->unselect();
	menuItemControllers[selectedMenuItemControllerIdx]->select();
}

void GUIMenuHeaderItemController::selectPrevious()
{
	determineMenuItemControllers();
	auto selectedMenuItemControllerIdx = getSelectedMenuItemControllerIdx();
	if (menuItemControllers.size() == 0) return;

	selectedMenuItemControllerIdx = (selectedMenuItemControllerIdx - 1) % menuItemControllers.size();
	if (selectedMenuItemControllerIdx < 0)
		selectedMenuItemControllerIdx += menuItemControllers.size();

	for (auto menuItemController: menuItemControllers) menuItemController->unselect();
	menuItemControllers[selectedMenuItemControllerIdx]->select();
}

void GUIMenuHeaderItemController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	GUIElementController::handleMouseEvent(node, event);
	if (disabled == true) return;
	auto elementNode  = dynamic_cast<GUIElementNode*>(this->node);
	if (event->getButton() == MOUSE_BUTTON_LEFT) {
		if (node == this->node && node->isEventBelongingToNode(event) == true) {
			auto& nodeConditions = (dynamic_cast<GUIElementNode*>(itemNode))->getActiveConditions();
			if (event->getType() == GUIMouseEvent::MOUSEEVENT_RELEASED) {
				event->setProcessed(true);
				toggleOpenState();
				node->getScreenNode()->getGUI()->setFoccussedNode(elementNode);
			}
		} else {
			if (open == true) {
				auto innerNode = this->node->getScreenNode()->getNodeById(this->node->getId() + "_inner");
				if (node == this->node && innerNode->isEventBelongingToNode(event) == false) {
					event->setProcessed(true);
					toggleOpenState();
				}
			}
		}
	}
}

void GUIMenuHeaderItemController::handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event)
{
	GUIElementController::handleKeyboardEvent(node, event);
	if (disabled == false && node == this->node) {
		switch (event->getKeyCode()) {
			case GUIKeyboardEvent::KEYCODE_UP: {
					event->setProcessed(true);
					if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
						Console::println("GUIMenuHeaderItemController::handleKeyboardEvent(): up");
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
					if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
						Console::println("GUIMenuHeaderItemController::handleKeyboardEvent(): down");
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
					if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
						toggleOpenState();
					}
					if (open == false) {
						node->getScreenNode()->delegateValueChanged(dynamic_cast<GUIElementNode*>(node));
					}
				}
				break;
		}
	}
	if (open == false) toggleOpenState();
}

void GUIMenuHeaderItemController::tick()
{
	GUIElementController::tick();
	if (open == true) node->getScreenNode()->getGUI()->addMouseOutClickCandidateElementNode(dynamic_cast< GUIElementNode* >(this->node));
}

void GUIMenuHeaderItemController::onFocusGained()
{
}

void GUIMenuHeaderItemController::onFocusLost()
{
}

bool GUIMenuHeaderItemController::hasValue()
{
	return true;
}

const MutableString& GUIMenuHeaderItemController::getValue()
{
	value.reset();
	return value;
}

void GUIMenuHeaderItemController::setValue(const MutableString& value)
{
}

