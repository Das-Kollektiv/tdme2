#include <agui/gui/elements/GUIMenuHeaderController.h>

#include <agui/agui.h>
#include <agui/gui/elements/GUIMenuHeaderItemController.h>
#include <agui/gui/elements/GUITabsController.h>
#include <agui/gui/elements/GUITabController.h>
#include <agui/gui/events/GUIKeyboardEvent.h>
#include <agui/gui/events/GUIMouseEvent.h>
#include <agui/gui/nodes/GUIElementNode.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUIParentNode.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/GUI.h>
#include <agui/utilities/Console.h>
#include <agui/utilities/MutableString.h>

using agui::gui::elements::GUIMenuHeaderController;
using agui::gui::elements::GUIMenuHeaderItemController;
using agui::gui::events::GUIKeyboardEvent;
using agui::gui::events::GUIMouseEvent;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUIParentNode;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::GUI;
using agui::utilities::Console;
using agui::utilities::MutableString;

GUIMenuHeaderController::GUIMenuHeaderController(GUINode* node)
	: GUINodeController(node)
{
	this->focus = false;
}

bool GUIMenuHeaderController::isDisabled()
{
	return false;
}

void GUIMenuHeaderController::setDisabled(bool disabled)
{
}

void GUIMenuHeaderController::initialize()
{
}

void GUIMenuHeaderController::dispose()
{
}

void GUIMenuHeaderController::postLayout()
{
}

bool GUIMenuHeaderController::hasFocus()
{
	return focus;
}

void GUIMenuHeaderController::determineMenuHeaderItemControllers()
{
	menuHeaderItemControllers.clear();
	vector<GUINode*> childControllerNodes;
	required_dynamic_cast<GUIParentNode*>(node)->getChildControllerNodes(childControllerNodes);
	for (auto i = 0; i < childControllerNodes.size(); i++) {
		auto childControllerNode = childControllerNodes[i];
		auto childController = childControllerNode->getController();
		if (dynamic_cast<GUIMenuHeaderItemController*>(childController) != nullptr) {
			auto menuHeaderItemController = required_dynamic_cast<GUIMenuHeaderItemController*>(childController);
			if (menuHeaderItemController == nullptr)
				continue;
			menuHeaderItemControllers.push_back(menuHeaderItemController);
		}
	}
}

bool GUIMenuHeaderController::isOpen() {
	if (menuHeaderItemControllerIdx == -1) return false;
	return menuHeaderItemControllers[menuHeaderItemControllerIdx]->isOpen() == true;
}

void GUIMenuHeaderController::unselect() {
	if (menuHeaderItemControllerIdx == -1) return;
	if (menuHeaderItemControllers[menuHeaderItemControllerIdx]->isOpen() == true) {
		menuHeaderItemControllers[menuHeaderItemControllerIdx]->toggleOpenState();
		menuHeaderItemControllers[menuHeaderItemControllerIdx]->unselect();
	}
}

void GUIMenuHeaderController::selectNext()
{
	unselect();
	if (menuHeaderItemControllers.empty() == true) return;

	auto disabledItems = 0;
	while (disabledItems < menuHeaderItemControllers.size()) {
		menuHeaderItemControllerIdx = (menuHeaderItemControllerIdx + 1) % (int)menuHeaderItemControllers.size();
		if (menuHeaderItemControllerIdx < 0)
			menuHeaderItemControllerIdx += menuHeaderItemControllers.size();
		if (menuHeaderItemControllers[menuHeaderItemControllerIdx]->isDisabled() == false) break;
		disabledItems++;
	}
	if (disabledItems == menuHeaderItemControllers.size()) {
		menuHeaderItemControllerIdx = -1;
		return;
	}

	menuHeaderItemControllers[menuHeaderItemControllerIdx]->select();
	if (menuHeaderItemControllers[menuHeaderItemControllerIdx]->isOpen() == false) menuHeaderItemControllers[menuHeaderItemControllerIdx]->toggleOpenState();
	menuHeaderItemControllers[menuHeaderItemControllerIdx]->selectFirst();
}

void GUIMenuHeaderController::selectPrevious()
{
	unselect();
	if (menuHeaderItemControllers.empty() == true) return;
	if (menuHeaderItemControllerIdx == -1) menuHeaderItemControllerIdx = (int)menuHeaderItemControllers.size();

	auto disabledItems = 0;
	while (disabledItems < menuHeaderItemControllers.size()) {
		menuHeaderItemControllerIdx = (menuHeaderItemControllerIdx - 1) % (int)menuHeaderItemControllers.size();
		if (menuHeaderItemControllerIdx < 0)
			menuHeaderItemControllerIdx += menuHeaderItemControllers.size();
		if (menuHeaderItemControllers[menuHeaderItemControllerIdx]->isDisabled() == false) break;
		disabledItems++;
	}
	if (disabledItems == menuHeaderItemControllers.size()) {
		menuHeaderItemControllerIdx = -1;
		return;
	}

	menuHeaderItemControllers[menuHeaderItemControllerIdx]->select();
	if (menuHeaderItemControllers[menuHeaderItemControllerIdx]->isOpen() == false) menuHeaderItemControllers[menuHeaderItemControllerIdx]->toggleOpenState();
	menuHeaderItemControllers[menuHeaderItemControllerIdx]->selectFirst();
}

void GUIMenuHeaderController::select(int idx) {
	unselect();
	menuHeaderItemControllerIdx = idx;
	menuHeaderItemControllers[menuHeaderItemControllerIdx]->select();
	if (menuHeaderItemControllers[menuHeaderItemControllerIdx]->isOpen() == false) menuHeaderItemControllers[menuHeaderItemControllerIdx]->toggleOpenState();
}

void GUIMenuHeaderController::select(GUIElementNode* elementNode) {
	auto selectedMenuHeaderItemController = required_dynamic_cast<GUIMenuHeaderItemController*>(elementNode->getController());
	auto i = 0;
	for (auto menuHeaderItemController: menuHeaderItemControllers) {
		if (menuHeaderItemController == selectedMenuHeaderItemController) {
			select(i);
			return;
		}
		i++;
	}
}

void GUIMenuHeaderController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	if (node == this->node && node->isEventBelongingToNode(event) && event->getButton() == MOUSE_BUTTON_LEFT) {
		event->setProcessed(true);
		if (event->getType() == GUIMouseEvent::MOUSEEVENT_RELEASED) {
			node->getScreenNode()->getGUI()->setFoccussedNode(required_dynamic_cast<GUIElementNode*>(node));
		}
	}
}

void GUIMenuHeaderController::handleKeyboardEvent(GUIKeyboardEvent* event)
{
	switch (event->getKeyCode()) {
		case GUIKeyboardEvent::KEYCODE_ESCAPE: {
			determineMenuHeaderItemControllers();
			if (menuHeaderItemControllers.empty() == true) return;
			if (menuHeaderItemControllerIdx == -1) return;
			if (menuHeaderItemControllers[menuHeaderItemControllerIdx]->isOpen() == true) menuHeaderItemControllers[menuHeaderItemControllerIdx]->toggleOpenState();
			menuHeaderItemControllers[menuHeaderItemControllerIdx]->unselect();
		}
		break;
	case GUIKeyboardEvent::KEYCODE_LEFT: {
			event->setProcessed(true);
			if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
				selectPrevious();
			}
		}
		break;
	case GUIKeyboardEvent::KEYCODE_RIGHT: {
			event->setProcessed(true);
			if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
				selectNext();
			}
		}
		break;
	case GUIKeyboardEvent::KEYCODE_UP: {
			event->setProcessed(true);
			if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
				if (menuHeaderItemControllers.empty() == true) return;
				if (menuHeaderItemControllerIdx == -1) menuHeaderItemControllerIdx = 0;
				if (menuHeaderItemControllers[menuHeaderItemControllerIdx]->isOpen() == false) {
					menuHeaderItemControllers[menuHeaderItemControllerIdx]->toggleOpenState();
					menuHeaderItemControllers[menuHeaderItemControllerIdx]->selectFirst();
				} else {
					menuHeaderItemControllers[menuHeaderItemControllerIdx]->selectPrevious();
				}
			}
		}
		break;
	case GUIKeyboardEvent::KEYCODE_DOWN: {
			event->setProcessed(true);
			if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
				if (menuHeaderItemControllers.empty() == true) return;
				if (menuHeaderItemControllerIdx == -1) menuHeaderItemControllerIdx = 0;
				if (menuHeaderItemControllers[menuHeaderItemControllerIdx]->isOpen() == false) {
					menuHeaderItemControllers[menuHeaderItemControllerIdx]->toggleOpenState();
					menuHeaderItemControllers[menuHeaderItemControllerIdx]->selectFirst();
				} else {
					menuHeaderItemControllers[menuHeaderItemControllerIdx]->selectNext();
				}
			}
		}
		break;
	case GUIKeyboardEvent::KEYCODE_SPACE: {
			determineMenuHeaderItemControllers();
			if (menuHeaderItemControllers.empty() == true) return;
			if (menuHeaderItemControllerIdx == -1) menuHeaderItemControllerIdx = 0;
			menuHeaderItemControllers[menuHeaderItemControllerIdx]->handleCurrentMenuItemKeyboardEvent(event);
		}
		break;
	}
}

void GUIMenuHeaderController::tick()
{
}

void GUIMenuHeaderController::onFocusGained()
{
	focus = true;
}

void GUIMenuHeaderController::onFocusLost()
{
	focus = false;
}

bool GUIMenuHeaderController::hasValue()
{
	return false;
}

const MutableString& GUIMenuHeaderController::getValue()
{
	return value;
}

void GUIMenuHeaderController::setValue(const MutableString& value)
{
}

void GUIMenuHeaderController::onSubTreeChange()
{
	determineMenuHeaderItemControllers();
	menuHeaderItemControllerIdx = -1;
}

