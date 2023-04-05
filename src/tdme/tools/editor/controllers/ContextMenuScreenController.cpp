#include <tdme/tools/editor/controllers/ContextMenuScreenController.h>

#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIChangeListener.h>
#include <tdme/gui/events/GUIFocusListener.h>
#include <tdme/gui/events/GUIInputEventHandler.h>
#include <tdme/gui/events/GUITooltipRequestListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/math/Math.h>
#include <tdme/tools/editor/controllers/TooltipScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/Properties.h>
#include <tdme/utilities/StringTools.h>

using tdme::tools::editor::controllers::ContextMenuScreenController;

using std::string;
using std::unordered_map;

using tdme::engine::Engine;
using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::events::GUIChangeListener;
using tdme::gui::events::GUIFocusListener;
using tdme::gui::events::GUIInputEventHandler;
using tdme::gui::events::GUITooltipRequestListener;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUINode_RequestedConstraints;
using tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUIParser;
using tdme::math::Math;
using tdme::tools::editor::controllers::TooltipScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::MutableString;
using tdme::utilities::Properties;
using tdme::utilities::StringTools;

ContextMenuScreenController::ContextMenuScreenController(PopUps* popUps): popUps(popUps)
{
}

ContextMenuScreenController::~ContextMenuScreenController()
{
	for (auto& actionIt: actions) delete actionIt.second;
	actions.clear();
	screenNode = nullptr;
}

GUIScreenNode* ContextMenuScreenController::getScreenNode()
{
	return screenNode;
}

void ContextMenuScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse("resources/engine/gui", "popup_contextmenu.xml");
		screenNode->setEnabled(false);
		screenNode->addActionListener(this);
		screenNode->addChangeListener(this);
		screenNode->addFocusListener(this);
		screenNode->addTooltipRequestListener(this);
		screenNode->setInputEventHandler(this);
		contextMenuNode = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("contextmenu"));
		tscriptMethods.load("resources/engine/code-completion/", "tscript-methods.properties");
	} catch (Exception& exception) {
		Console::println("ContextMenuScreenController::initialize(): An error occurred: " + string(exception.what()));
	}
}

void ContextMenuScreenController::dispose()
{
}

void ContextMenuScreenController::show(int mouseX, int mouseY)
{
	auto x = static_cast<int>((float)mouseX * (float)screenNode->getScreenWidth() / (float)Engine::getInstance()->getGUI()->getWidth());
	auto y = static_cast<int>((float)mouseY * (float)screenNode->getScreenHeight() / (float)Engine::getInstance()->getGUI()->getHeight());
	x = Math::min(x, screenNode->getScreenWidth() - contextMenuNode->getComputedConstraints().width);
	y = Math::min(y, screenNode->getScreenHeight() - contextMenuNode->getComputedConstraints().height);
	contextMenuNode->getRequestsConstraints().leftType = GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL;
	contextMenuNode->getRequestsConstraints().left = x;
	contextMenuNode->getRequestsConstraints().topType = GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL;
	contextMenuNode->getRequestsConstraints().top = y;
	screenNode->setEnabled(true);
	screenNode->layout();
	Engine::getInstance()->getGUI()->setFoccussedNode(contextMenuNode);
}

void ContextMenuScreenController::close()
{
	screenNode->setEnabled(false);
}

void ContextMenuScreenController::onAction(GUIActionListenerType type, GUIElementNode* node)
{
	if (type == GUIActionListenerType::PERFORMED) {
		auto actionIt = actions.find(node->getId());
		if (actionIt != actions.end()) {
			close();
			if (actionIt->second != nullptr) actionIt->second->performAction();
		}
	}
}

void ContextMenuScreenController::onChange(GUIElementNode* node) {
	if (node->getId() == "context_menu_addnode_search") {
		//
		required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("context_menu_addnode_list"))->clearSubNodes();
		//
		auto searchValue = StringTools::toLowerCase(node->getController()->getValue().getString());
		auto& properties = tscriptMethods.getProperties();
		for (const auto& propertyIt: properties) {
			auto methodNameCandidate = propertyIt.first;
			auto methodDescription = propertyIt.second;
			auto methodName = string("unknown");
			if (StringTools::startsWith(methodNameCandidate, "miniscript.basemethod.") == true) {
				methodName = StringTools::substring(methodNameCandidate, string("miniscript.basemethod.").size());
			} else
			if (StringTools::startsWith(methodNameCandidate, "miniscript.logicmethod.") == true) {
				methodName = StringTools::substring(methodNameCandidate, string("miniscript.logicmethod.").size());
			} else
			if (StringTools::startsWith(methodNameCandidate, "miniscript.") == true) {
				methodName = StringTools::substring(methodNameCandidate, string("miniscript.").size());
			}
			if (StringTools::toLowerCase(methodName).find(searchValue) != string::npos) {
				required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("context_menu_addnode_list"))->addSubNodes(
					"<context-menu-item template=\"context-menu-item_template_addnode.xml\" category=\"" + GUIParser::escapeQuotes(methodName) + "\" name=\"" + GUIParser::escapeQuotes(methodDescription) + "\" />",
					true
				);
			}
		}
	}
}

void ContextMenuScreenController::onFocus(GUIElementNode* node) {
	GUI::setDisableTabFocusControl(node->getScreenNode() != screenNode);
}

void ContextMenuScreenController::onUnfocus(GUIElementNode* node) {
}

void ContextMenuScreenController::clear() {
	required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(contextMenuNode->getId()))->clearSubNodes();
	for (auto& actionIt: actions) delete actionIt.second;
	actions.clear();
}

void ContextMenuScreenController::setupVisualCodeAddNodeContextMenu() {
	required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(contextMenuNode->getId()))->addSubNodes(
		"<template src=\"resources/engine/gui/template_visualcode_addnodemenu.xml\" />",
		true
	);
	//
	required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("context_menu_addnode_list"))->clearSubNodes();
	//
	auto& properties = tscriptMethods.getProperties();
	for (const auto& propertyIt: properties) {
		auto methodNameCandidate = propertyIt.first;
		auto methodDescription = propertyIt.second;
		auto methodName = string("unknown");
		if (StringTools::startsWith(methodNameCandidate, "miniscript.basemethod.") == true) {
			methodName = StringTools::substring(methodNameCandidate, string("miniscript.basemethod.").size());
		} else
		if (StringTools::startsWith(methodNameCandidate, "miniscript.logicmethod.") == true) {
			methodName = StringTools::substring(methodNameCandidate, string("miniscript.logicmethod.").size());
		} else
		if (StringTools::startsWith(methodNameCandidate, "miniscript.") == true) {
			methodName = StringTools::substring(methodNameCandidate, string("miniscript.").size());
		}
		required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById("context_menu_addnode_list"))->addSubNodes(
			"<context-menu-item template=\"context-menu-item_template_addnode.xml\" category=\"" + GUIParser::escapeQuotes(methodName) + "\" name=\"" + GUIParser::escapeQuotes(methodDescription) + "\" />",
			true
		);
	}
}

void ContextMenuScreenController::addMenuItem(const string& text, const string& id, Action* action) {
	required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(contextMenuNode->getId()))->addSubNodes(
		"<context-menu-item text=\"" + GUIParser::escapeQuotes(text) + "\" id=\"" + GUIParser::escapeQuotes(id) + "\" />",
		true
	);
	auto actionIt = actions.find(id);
	if (actionIt != actions.end() && actionIt->second != nullptr) delete actionIt->second;
	if (action != nullptr) actions[id] = action;
}

void ContextMenuScreenController::addMenuSeparator() {
	required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(contextMenuNode->getId()))->addSubNodes(
		"<menu-separator />",
		true
	);
}

void ContextMenuScreenController::onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) {
	popUps->getTooltipScreenController()->show(mouseX, mouseY, node->getToolTip());
}

void ContextMenuScreenController::onTooltipCloseRequest() {
	popUps->getTooltipScreenController()->close();
}

void ContextMenuScreenController::handleInputEvents() {
	auto& mouseEvents = Engine::getInstance()->getGUI()->getMouseEvents();
	auto& keyboardEvents = Engine::getInstance()->getGUI()->getKeyboardEvents();
	for (auto& event: mouseEvents) {
		if (event.isProcessed() == true) continue;
		if (event.getType() == GUIMouseEvent::MOUSEEVENT_RELEASED &&
			(event.getButton() == MOUSE_BUTTON_LEFT ||
			event.getButton() == MOUSE_BUTTON_MIDDLE ||
			event.getButton() == MOUSE_BUTTON_RIGHT)) {
			close();
			return;
		}
	}
	for (auto& event: keyboardEvents) {
		if (event.isProcessed() == true) continue;
		if (event.getKeyCode() == GUIKeyboardEvent::KEYCODE_ESCAPE) {
			close();
			return;
		}
	}
}
