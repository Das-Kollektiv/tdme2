#include <tdme/gui/elements/GUIMenuHeaderController.h>

#include <tdme/gui/GUI.h>
#include <tdme/gui/elements/GUIMenuHeaderItemController.h>
#include <tdme/gui/elements/GUITabController.h>
#include <tdme/gui/elements/GUITabsController.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/utilities/Console.h>

using tdme::gui::elements::GUIMenuHeaderController;
using tdme::gui::GUI;
using tdme::gui::elements::GUIMenuHeaderItemController;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::utilities::Console;

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

void GUIMenuHeaderController::unselect()
{
	(dynamic_cast< GUIParentNode* >(node))->getChildControllerNodes(childControllerNodes);
	for (auto i = 0; i < childControllerNodes.size(); i++) {
		auto childControllerNode = childControllerNodes[i];
		auto childController = childControllerNode->getController();
		if (dynamic_cast< GUITabController* >(childController) != nullptr) {
			auto menuHeaderItemController = dynamic_cast< GUIMenuHeaderItemController* >(childController);
			if (menuHeaderItemController != nullptr) menuHeaderItemController->unselect();
		}
	}
}

void GUIMenuHeaderController::determineMenuHeaderItemControllers()
{
	menuHeaderItemControllers.clear();
	(dynamic_cast< GUIParentNode* >(node))->getChildControllerNodes(childControllerNodes);
	for (auto i = 0; i < childControllerNodes.size(); i++) {
		auto childControllerNode = childControllerNodes[i];
		auto childController = childControllerNode->getController();
		if (dynamic_cast< GUIMenuHeaderItemController* >(childController) != nullptr) {
			auto guiTabController = dynamic_cast< GUIMenuHeaderItemController* >(childController);
			if (static_cast< GUINode* >(guiTabController->getNode()->getParentControllerNode()) != node)
				continue;

			if (guiTabController->isDisabled() == true)
				continue;

			menuHeaderItemControllers.push_back(guiTabController);
		}
	}
}

int32_t GUIMenuHeaderController::getSelectedHeaderItemIdx()
{
	auto tabControllerIdx = 0;
	for (auto i = 0; i < menuHeaderItemControllers.size(); i++) {
		auto tabController = menuHeaderItemControllers[i];
		if (tabController->isSelected() == true) {
			tabControllerIdx = i;
			break;
		}
	}
	return tabControllerIdx;
}

void GUIMenuHeaderController::selectNext()
{
	determineMenuHeaderItemControllers();
	auto tabControllerIdx = getSelectedHeaderItemIdx();
	unselect();
	tabControllerIdx = (tabControllerIdx + 1) % menuHeaderItemControllers.size();
	if (tabControllerIdx < 0)
		tabControllerIdx += menuHeaderItemControllers.size();

	for (auto menuHeaderItemController: menuHeaderItemControllers) {
		if (menuHeaderItemController->isOpen() == true) menuHeaderItemControllers[tabControllerIdx]->toggleOpenState();
	}
	if (menuHeaderItemControllers[tabControllerIdx]->isOpen() == false) menuHeaderItemControllers[tabControllerIdx]->toggleOpenState();
}

void GUIMenuHeaderController::selectPrevious()
{
	determineMenuHeaderItemControllers();
	auto tabControllerIdx = getSelectedHeaderItemIdx();
	unselect();
	tabControllerIdx = (tabControllerIdx - 1) % menuHeaderItemControllers.size();
	if (tabControllerIdx < 0)
		tabControllerIdx += menuHeaderItemControllers.size();

	for (auto menuHeaderItemController: menuHeaderItemControllers) {
		if (menuHeaderItemController->isOpen() == true) menuHeaderItemControllers[tabControllerIdx]->toggleOpenState();
	}
	if (menuHeaderItemControllers[tabControllerIdx]->isOpen() == false) menuHeaderItemControllers[tabControllerIdx]->toggleOpenState();
}

void GUIMenuHeaderController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	if (node == this->node && node->isEventBelongingToNode(event) && event->getButton() == MOUSE_BUTTON_LEFT) {
		event->setProcessed(true);
		if (event->getType() == GUIMouseEvent::MOUSEEVENT_RELEASED) {
			node->getScreenNode()->getGUI()->setFoccussedNode(dynamic_cast< GUIElementNode* >(node));
		}
	}
}

void GUIMenuHeaderController::handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event)
{
	if (node == this->node) {
		switch (event->getKeyCode()) {
		case GUIKeyboardEvent::KEYCODE_LEFT: {
				event->setProcessed(true);
				if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
					Console::println("GUIMenuHeaderController::handleKeyboardEvent(): left");
					selectPrevious();
				}
			}
			break;
		case GUIKeyboardEvent::KEYCODE_RIGHT: {
				event->setProcessed(true);
				if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
					Console::println("GUIMenuHeaderController::handleKeyboardEvent(): right");
					selectNext();
				}
			}
			break;
		}

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

