#include <tdme/gui/elements/GUITabsController.h>

#include <tdme/tdme.h>
#include <tdme/gui/elements/GUITabsHeaderController.h>
#include <tdme/gui/elements/GUITabContentController.h>
#include <tdme/gui/elements/GUITabController.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MutableString.h>

using tdme::gui::elements::GUITabsController;

using tdme::gui::elements::GUITabsHeaderController;
using tdme::gui::elements::GUITabContentController;
using tdme::gui::elements::GUITabController;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUI;
using tdme::utilities::Console;
using tdme::utilities::MutableString;

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
