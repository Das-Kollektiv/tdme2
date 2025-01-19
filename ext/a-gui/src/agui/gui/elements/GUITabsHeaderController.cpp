
#include <agui/gui/elements/GUITabsHeaderController.h>

#include <agui/agui.h>
#include <agui/gui/elements/GUITabsController.h>
#include <agui/gui/elements/GUITabController.h>
#include <agui/gui/events/GUIKeyboardEvent.h>
#include <agui/gui/events/GUIMouseEvent.h>
#include <agui/gui/nodes/GUIElementController.h>
#include <agui/gui/nodes/GUIElementNode.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUIParentNode.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/GUI.h>
#include <agui/utilities/MutableString.h>

using agui::gui::elements::GUITabsController;
using agui::gui::elements::GUITabsHeaderController;
using agui::gui::elements::GUITabController;
using agui::gui::events::GUIKeyboardEvent;
using agui::gui::events::GUIMouseEvent;
using agui::gui::nodes::GUIElementController;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUIParentNode;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::GUI;
using agui::utilities::MutableString;

GUITabsHeaderController::GUITabsHeaderController(GUINode* node)
	: GUIElementController(node)
{
	this->focus = false;
}

bool GUITabsHeaderController::isDisabled()
{
	return false;
}

void GUITabsHeaderController::setDisabled(bool disabled)
{
}

void GUITabsHeaderController::initialize()
{
	tabsNode = required_dynamic_cast<GUIParentNode*>(node)->getParentControllerNode();

	//
	GUIElementController::initialize();

	//
	determineTabControllers();
	selectCurrent();
}

void GUITabsHeaderController::dispose()
{
	GUIElementController::dispose();
}

void GUITabsHeaderController::postLayout()
{
}

bool GUITabsHeaderController::hasFocus()
{
	return focus;
}

void GUITabsHeaderController::unselect()
{
	if (tabControllerIdx == -1) return;
	tabControllers[tabControllerIdx]->setSelected(false);
}

void GUITabsHeaderController::select()
{
	if (tabControllerIdx == -1) return;
	tabControllers[tabControllerIdx]->setSelected(true);
}

void GUITabsHeaderController::select(int idx) {
	unselect();
	tabControllerIdx = idx;
	if (tabControllerIdx >= tabControllers.size()) tabControllerIdx = tabControllers.size() - 1;
	select();
}

void GUITabsHeaderController::select(GUIElementNode* tabElementNode) {
	auto tabElementNodeController = tabElementNode->getController();
	auto i = 0;
	for (auto tabController: tabControllers) {
		if (tabElementNodeController == tabController) {
			select(i);
			break;
		}
		i++;
	}
}

void GUITabsHeaderController::determineTabControllers()
{
	vector<GUINode*> childControllerNodes;
	tabControllers.clear();
	required_dynamic_cast<GUIParentNode*>(node)->getChildControllerNodes(childControllerNodes);
	for (auto i = 0; i < childControllerNodes.size(); i++) {
		auto childControllerNode = childControllerNodes[i];
		auto childController = childControllerNode->getController();
		if (dynamic_cast<GUITabController*>(childController) != nullptr) {
			auto guiTabController = required_dynamic_cast<GUITabController*>(childController);
			if (static_cast<GUINode*>(guiTabController->getNode()->getParentControllerNode()) != node)
				continue;
			tabControllers.push_back(guiTabController);
		}
	}
}

void GUITabsHeaderController::selectNext()
{
	if (tabControllers.empty() == true) return;
	if (tabControllerIdx == -1) tabControllerIdx = 0;
	unselect();
	tabControllerIdx = (tabControllerIdx + 1) % (int)tabControllers.size();
	if (tabControllerIdx < 0)
		tabControllerIdx += tabControllers.size();

	select();
	auto guiTabsController = required_dynamic_cast<GUITabsController*>(tabsNode->getController());
	guiTabsController->setTabContentSelected(tabControllers[tabControllerIdx]->getNode()->getId());
}

void GUITabsHeaderController::selectPrevious()
{
	if (tabControllers.empty() == true) return;
	if (tabControllerIdx == -1) tabControllerIdx = 0;
	unselect();
	tabControllerIdx = (tabControllerIdx - 1) % (int)tabControllers.size();
	if (tabControllerIdx < 0)
		tabControllerIdx += tabControllers.size();

	select();
	auto guiTabsController = required_dynamic_cast<GUITabsController*>(tabsNode->getController());
	guiTabsController->setTabContentSelected(tabControllers[tabControllerIdx]->getNode()->getId());
}

void GUITabsHeaderController::selectCurrent()
{
	if (tabControllers.empty() == true) return;
	unselect();
	if (tabControllerIdx == -1) tabControllerIdx = 0;
	if (tabControllerIdx >= tabControllers.size()) tabControllerIdx = tabControllers.size() - 1;
	select();
	auto guiTabsController = required_dynamic_cast<GUITabsController*>(tabsNode->getController());
	if (guiTabsController->getValue().equals(tabControllers[tabControllerIdx]->getNode()->getId()) == false) {
		guiTabsController->setTabContentSelected(tabControllers[tabControllerIdx]->getNode()->getId());
	}
}

void GUITabsHeaderController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	GUIElementController::handleMouseEvent(node, event);
	if (node == this->node && node->isEventBelongingToNode(event) && event->getButton() == MOUSE_BUTTON_LEFT) {
		event->setProcessed(true);
		if (event->getType() == GUIMouseEvent::MOUSEEVENT_RELEASED) {
			node->getScreenNode()->getGUI()->setFoccussedNode(required_dynamic_cast<GUIElementNode*>(node));
		}
	}
}

void GUITabsHeaderController::handleKeyboardEvent(GUIKeyboardEvent* event)
{
	GUIElementController::handleKeyboardEvent(event);
	switch (event->getKeyCode()) {
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
	}
}

void GUITabsHeaderController::tick()
{
	GUIElementController::tick();
}

void GUITabsHeaderController::onFocusGained()
{
	focus = true;
	selectCurrent();
}

void GUITabsHeaderController::onFocusLost()
{
	focus = false;
	selectCurrent();
}

bool GUITabsHeaderController::hasValue()
{
	return false;
}

const MutableString& GUITabsHeaderController::getValue()
{
	return value;
}

void GUITabsHeaderController::setValue(const MutableString& value)
{
}

void GUITabsHeaderController::onSubTreeChange() {
	determineTabControllers();
	if (tabControllerIdx == -1) tabControllerIdx = 0;
	if (tabControllerIdx >= tabControllers.size()) tabControllerIdx = tabControllers.size() - 1;
	selectCurrent();
}


