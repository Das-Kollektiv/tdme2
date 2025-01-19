#include <agui/gui/elements/GUIContextMenuController.h>

#include <string>

#include <agui/agui.h>
#include <agui/gui/elements/GUIContextMenuController.h>
#include <agui/gui/elements/GUIContextMenuItemController.h>
#include <agui/gui/events/GUIKeyboardEvent.h>
#include <agui/gui/events/GUIMouseEvent.h>
#include <agui/gui/nodes/GUIElementController.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUIParentNode.h>
#include <agui/gui/GUI.h>
#include <agui/utilities/Console.h>
#include <agui/utilities/MutableString.h>
#include <agui/utilities/StringTools.h>

using std::to_string;

using agui::gui::elements::GUIContextMenuController;
using agui::gui::elements::GUIContextMenuItemController;
using agui::gui::events::GUIKeyboardEvent;
using agui::gui::events::GUIMouseEvent;
using agui::gui::nodes::GUIElementController;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUIParentNode;
using agui::gui::GUI;
using agui::utilities::Console;
using agui::utilities::MutableString;
using agui::utilities::StringTools;

GUIContextMenuController::GUIContextMenuController(GUINode* node)
	: GUIElementController(node)
{
}

void GUIContextMenuController::initialize()
{
	//
	GUIElementController::initialize();
}

void GUIContextMenuController::dispose()
{
	GUIElementController::dispose();
}

void GUIContextMenuController::postLayout()
{
}

void GUIContextMenuController::determineMenuItemControllers()
{
	vector<GUINode*> childControllerNodes;
	menuItemControllers.clear();
	required_dynamic_cast<GUIParentNode*>(node)->getChildControllerNodes(childControllerNodes);
	for (auto i = 0; i < childControllerNodes.size(); i++) {
		auto childControllerNode = childControllerNodes[i];
		auto childController = childControllerNode->getController();
		auto menuItemController = dynamic_cast<GUIContextMenuItemController*>(childController);
		if (menuItemController != nullptr) {
			menuItemControllers.push_back(menuItemController);
		}
	}
}

void GUIContextMenuController::unselectSelection()
{
	if (selectedMenuItemControllerIdx == -1) return;
	if (menuItemControllers.empty() == true) return;
	menuItemControllers[selectedMenuItemControllerIdx]->unselect();
}

void GUIContextMenuController::selectFirst()
{
	unselectSelection();
	if (menuItemControllers.empty() == true) return;
	selectedMenuItemControllerIdx = -1;
	selectNext();
}

void GUIContextMenuController::selectNext()
{
	unselectSelection();
	if (menuItemControllers.empty() == true) return;

	auto disabledItems = 0;
	while (disabledItems < menuItemControllers.size()) {
		selectedMenuItemControllerIdx = (selectedMenuItemControllerIdx + 1) % (int)menuItemControllers.size();
		if (selectedMenuItemControllerIdx < 0)
			selectedMenuItemControllerIdx += menuItemControllers.size();
		if (menuItemControllers[selectedMenuItemControllerIdx]->isDisabled() == false) break;
		disabledItems++;
	}

	if (disabledItems == menuItemControllers.size()) {
		selectedMenuItemControllerIdx = -1;
		return;
	}

	menuItemControllers[selectedMenuItemControllerIdx]->select();
}

void GUIContextMenuController::selectPrevious()
{
	unselectSelection();
	if (menuItemControllers.empty() == true) return;
	if (selectedMenuItemControllerIdx == -1) selectedMenuItemControllerIdx = (int)menuItemControllers.size();

	auto disabledItems = 0;
	while (disabledItems < menuItemControllers.size()) {
		selectedMenuItemControllerIdx = (selectedMenuItemControllerIdx - 1) % (int)menuItemControllers.size();
		if (selectedMenuItemControllerIdx < 0)
			selectedMenuItemControllerIdx += menuItemControllers.size();
		if (menuItemControllers[selectedMenuItemControllerIdx]->isDisabled() == false) break;
		disabledItems++;
	}

	if (disabledItems == menuItemControllers.size()) {
		selectedMenuItemControllerIdx = -1;
		return;
	}

	menuItemControllers[selectedMenuItemControllerIdx]->select();
}

void GUIContextMenuController::handleCurrentMenuItemKeyboardEvent(GUIKeyboardEvent* event)
{
	determineMenuItemControllers();
	if (selectedMenuItemControllerIdx == -1) return;
	menuItemControllers[selectedMenuItemControllerIdx]->handleKeyboardEvent(event);
}

void GUIContextMenuController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	GUIElementController::handleMouseEvent(node, event);
}

void GUIContextMenuController::handleKeyboardEvent(GUIKeyboardEvent* event)
{
	GUIElementController::handleKeyboardEvent(event);
	if (event->isProcessed() == true) return;
	switch (event->getKeyCode()) {
	case GUIKeyboardEvent::KEYCODE_UP: {
			event->setProcessed(true);
			if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
				selectPrevious();
			}
		}
		break;
	case GUIKeyboardEvent::KEYCODE_DOWN: {
			event->setProcessed(true);
			if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
				selectNext();
			}
		}
		break;
	}
}

void GUIContextMenuController::tick()
{
	GUIElementController::tick();
}

void GUIContextMenuController::onFocusGained()
{
}

void GUIContextMenuController::onFocusLost()
{
}

bool GUIContextMenuController::hasValue()
{
	return true;
}

const MutableString& GUIContextMenuController::getValue()
{
	value.reset();
	return value;
}

void GUIContextMenuController::setValue(const MutableString& value)
{
	determineMenuItemControllers();
}

void GUIContextMenuController::onSubTreeChange() {
	determineMenuItemControllers();
	selectedMenuItemControllerIdx = -1;
}
