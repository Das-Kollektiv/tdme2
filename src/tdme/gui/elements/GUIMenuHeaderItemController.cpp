#include <tdme/gui/elements/GUIMenuHeaderItemController.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/elements/GUIMenuHeaderController.h>
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
#include <tdme/gui/GUI.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

using std::to_string;

using tdme::gui::elements::GUIMenuHeaderController;
using tdme::gui::elements::GUIMenuHeaderItemController;
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
using tdme::gui::GUI;
using tdme::utilities::Console;
using tdme::utilities::MutableString;
using tdme::utilities::StringTools;

string GUIMenuHeaderItemController::CONDITION_OPENED = "opened";
string GUIMenuHeaderItemController::CONDITION_CLOSED = "closed";
string GUIMenuHeaderItemController::CONDITION_SELECTED = "selected";
string GUIMenuHeaderItemController::CONDITION_UNSELECTED = "unselected";


GUIMenuHeaderItemController::GUIMenuHeaderItemController(GUINode* node)
	: GUIElementController(node)
{
	this->selected = required_dynamic_cast<GUIElementNode*>(node)->isSelected();
	this->open = false;
}

bool GUIMenuHeaderItemController::isSelected()
{
	return selected;
}

void GUIMenuHeaderItemController::select()
{
	auto& nodeConditions = required_dynamic_cast<GUIElementNode*>(node)->getActiveConditions();
	nodeConditions.remove(this->selected == true?CONDITION_SELECTED:CONDITION_UNSELECTED);
	this->selected = true;
	nodeConditions.add(this->selected == true?CONDITION_SELECTED:CONDITION_UNSELECTED);
}

void GUIMenuHeaderItemController::unselect()
{
	auto& nodeConditions = required_dynamic_cast<GUIElementNode*>(node)->getActiveConditions();
	nodeConditions.remove(this->selected == true?CONDITION_SELECTED:CONDITION_UNSELECTED);
	this->selected = false;
	nodeConditions.add(this->selected == true?CONDITION_SELECTED:CONDITION_UNSELECTED);
}

void GUIMenuHeaderItemController::initialize()
{
	required_dynamic_cast<GUIElementNode*>(node)->getActiveConditions().add(open == true?CONDITION_OPENED:CONDITION_CLOSED);

	//
	GUIElementController::initialize();

	//
	if (this->selected == true) select(); else unselect();

	//
	menuHeaderNode = dynamic_cast<GUIElementNode*>(node->getParentControllerNode());
	while (true == true) {
		if (dynamic_cast<GUIMenuHeaderController*>(menuHeaderNode->getController()) != nullptr) {
			break;
		}
		menuHeaderNode = dynamic_cast<GUIElementNode*>(menuHeaderNode->getParentControllerNode());
	}
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
	required_dynamic_cast<GUIElementNode*>(node)->getActiveConditions().remove(open == true?CONDITION_OPENED:CONDITION_CLOSED);
	open = open == true?false:true;
	required_dynamic_cast<GUIElementNode*>(node)->getActiveConditions().add(open == true?CONDITION_OPENED:CONDITION_CLOSED);
	if (open == true) select(); else unselect();
}

void GUIMenuHeaderItemController::determineMenuItemControllers()
{
	vector<GUINode*> childControllerNodes;
	menuItemControllers.clear();
	required_dynamic_cast<GUIParentNode*>(node)->getChildControllerNodes(childControllerNodes);
	for (auto i = 0; i < childControllerNodes.size(); i++) {
		auto childControllerNode = childControllerNodes[i];
		auto childController = childControllerNode->getController();
		auto menuItemController = dynamic_cast<GUIMenuItemController*>(childController);
		if (menuItemController != nullptr) {
			menuItemControllers.push_back(menuItemController);
		}
	}
}

void GUIMenuHeaderItemController::unselectSelection()
{
	if (selectedMenuItemControllerIdx == -1) return;
	if (menuItemControllers.empty() == true) return;
	menuItemControllers[selectedMenuItemControllerIdx]->unselect();
}

void GUIMenuHeaderItemController::selectFirst()
{
	unselectSelection();
	if (menuItemControllers.empty() == true) return;
	selectedMenuItemControllerIdx = -1;
	selectNext();
}

void GUIMenuHeaderItemController::selectNext()
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

void GUIMenuHeaderItemController::selectPrevious()
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

	menuItemControllers[selectedMenuItemControllerIdx]->select();}

void GUIMenuHeaderItemController::handleCurrentMenuItemKeyboardEvent(GUIKeyboardEvent* event)
{
	determineMenuItemControllers();
	if (selectedMenuItemControllerIdx == -1) return;
	menuItemControllers[selectedMenuItemControllerIdx]->handleKeyboardEvent(event);
}

void GUIMenuHeaderItemController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	GUIElementController::handleMouseEvent(node, event);
	if (isDisabled() == true) return;
	auto elementNode  = required_dynamic_cast<GUIElementNode*>(this->node);
	auto menuHeaderController = required_dynamic_cast<GUIMenuHeaderController*>(menuHeaderNode->getController());
	auto menuOpened = menuHeaderController->isOpen();
	if (menuOpened == false) {
		if (node == this->node &&
			event->getButton() == MOUSE_BUTTON_LEFT &&
			event->getType() == GUIMouseEvent::MOUSEEVENT_RELEASED &&
			node->isEventBelongingToNode(event) == true) {
			if (open == false) {
				event->setProcessed(true);
				unselect();
				menuHeaderController->select(required_dynamic_cast<GUIElementNode*>(this->node));
			}
		}
	} else {
		if (open == true &&
			node == this->node &&
			event->getButton() == MOUSE_BUTTON_LEFT &&
			event->getType() == GUIMouseEvent::MOUSEEVENT_RELEASED) {
			auto innerNode = this->node->getScreenNode()->getNodeById(this->node->getId() + "_inner");
			if (innerNode->isEventBelongingToNode(event) == false) {
				event->setProcessed(true);
				menuHeaderController->unselect();
			}
		} else
		if (node == this->node &&
			event->getType() == GUIMouseEvent::MOUSEEVENT_MOVED) {
			if (node == this->node && node->isEventBelongingToNode(event) == true) {
				if (open == false) {
					event->setProcessed(true);
					menuHeaderController->select(required_dynamic_cast<GUIElementNode*>(this->node));				}
			}
		}
	}
}

void GUIMenuHeaderItemController::handleKeyboardEvent(GUIKeyboardEvent* event)
{
	GUIElementController::handleKeyboardEvent(event);
}

void GUIMenuHeaderItemController::tick()
{
	GUIElementController::tick();
	if (open == true) node->getScreenNode()->getGUI()->addMouseOutClickCandidateElementNode(required_dynamic_cast<GUIElementNode*>(this->node));
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
	determineMenuItemControllers();
}

void GUIMenuHeaderItemController::onSubTreeChange() {
	determineMenuItemControllers();
	selectedMenuItemControllerIdx = -1;
}
