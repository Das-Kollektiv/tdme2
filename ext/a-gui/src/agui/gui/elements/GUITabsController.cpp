#include <agui/gui/elements/GUITabsController.h>

#include <agui/agui.h>
#include <agui/gui/elements/GUITabsHeaderController.h>
#include <agui/gui/elements/GUITabContentController.h>
#include <agui/gui/elements/GUITabController.h>
#include <agui/gui/nodes/GUIElementNode.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUIParentNode.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/GUI.h>
#include <agui/utilities/Console.h>
#include <agui/utilities/MutableString.h>

using agui::gui::elements::GUITabsController;

using agui::gui::elements::GUITabsHeaderController;
using agui::gui::elements::GUITabContentController;
using agui::gui::elements::GUITabController;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUIParentNode;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::GUI;
using agui::utilities::Console;
using agui::utilities::MutableString;

GUITabsController::GUITabsController(GUINode* node)
	: GUINodeController(node)
{
}

void GUITabsController::determineTabContentControllers() {
	tabContentControllers.clear();
	vector<GUINode*> childControllerNodes;
	required_dynamic_cast<GUIParentNode*>(node)->getChildControllerNodes(childControllerNodes);
	for (auto i = 0; i < childControllerNodes.size(); i++) {
		auto childControllerNode = childControllerNodes[i];
		auto childController = childControllerNode->getController();
		if (dynamic_cast<GUITabContentController*>(childController) != nullptr) {
			auto tabContentController = required_dynamic_cast<GUITabContentController*>(childController);
			if (static_cast<GUINode*>(tabContentController->getNode()->getParentControllerNode()->getParentControllerNode()) != node)
				continue;
			tabContentControllers.push_back(tabContentController);
		}
	}
}

bool GUITabsController::isDisabled()
{
	return false;
}

void GUITabsController::setDisabled(bool disabled)
{
}

void GUITabsController::initialize()
{
	determineTabContentControllers();
	vector<GUINode*> childControllerNodes;
	required_dynamic_cast<GUIParentNode*>(node)->getChildControllerNodes(childControllerNodes);
	for (auto i = 0; i < childControllerNodes.size(); i++) {
		auto childControllerNode = childControllerNodes[i];
		auto childController = childControllerNode->getController();
		if (dynamic_cast<GUITabsHeaderController*>(childController) != nullptr) {
			auto _tabsHeaderController = required_dynamic_cast<GUITabsHeaderController*>(childController);
			if (static_cast<GUINode*>(_tabsHeaderController->getNode()->getParentControllerNode()) != node)
				continue;
			tabsHeaderController = _tabsHeaderController;
		}
	}
	auto preselectedTabIdx = 0;
	auto i = 0;
	for (auto tabContentController: tabContentControllers) {
		if (tabContentController->isSelected() == true) preselectedTabIdx = i;
		i++;
	}
	tabsHeaderController->select(preselectedTabIdx);
}

void GUITabsController::dispose()
{
}

void GUITabsController::postLayout()
{
}

void GUITabsController::unselect()
{
	tabsHeaderController->unselect();
}

void GUITabsController::select(GUIElementNode* tabElementNode) {
	tabsHeaderController->select(tabElementNode);
}

void GUITabsController::setTabContentSelectedInternal(const string& id) {
	// TODO: a.drewke: improve me!
	if (value.equals(id) == true && tabSelected == true) return;
	tabSelected = false;
	auto tabContentNodeId = id + "-content";
	for (auto tabContentController: tabContentControllers) {
		auto select = tabContentNodeId == tabContentController->getNode()->getId();
		tabContentController->setSelected(select);
		if (select == true) tabSelected = true;
	}
	value.set(tabSelected == true?id:string());
}

void GUITabsController::setTabContentSelected(const string& id)
{
	setTabContentSelectedInternal(id);
	// TODO: a.drewke, no element node, so it cant delegate value changes
	// node->getScreenNode()->delegateValueChanged(required_dynamic_cast<GUIElementNode*>(node));
}

void GUITabsController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
}

void GUITabsController::handleKeyboardEvent(GUIKeyboardEvent* event)
{
}

void GUITabsController::tick()
{
}

void GUITabsController::onFocusGained()
{
}

void GUITabsController::onFocusLost()
{
}

bool GUITabsController::hasValue()
{
	return true;
}

const MutableString& GUITabsController::getValue()
{
	return value;
}

void GUITabsController::setValue(const MutableString& value)
{
	auto tabElementNode = dynamic_cast<GUIElementNode*>(node->getScreenNode()->getNodeById(value.getString()));
	if (tabElementNode != nullptr) {
		tabsHeaderController->select(tabElementNode);
		setTabContentSelected(tabElementNode->getId());
	} else {
		Console::printLine("GUITabsController::setValue(): tab with id '" + value.getString() + "' not found");
	}
}

void GUITabsController::onSubTreeChange()
{
	tabSelected = false;
	determineTabContentControllers();
	setTabContentSelectedInternal(value.getString());
}
