#include <tdme/gui/elements/GUIContextMenuController.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/elements/GUIContextMenuController.h>
#include <tdme/gui/elements/GUIContextMenuItemController.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIElementController.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

using std::to_string;

using tdme::gui::elements::GUIContextMenuController;
using tdme::gui::elements::GUIContextMenuItemController;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementController;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::GUI;
using tdme::utilities::Console;
using tdme::utilities::MutableString;
using tdme::utilities::StringTools;

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
