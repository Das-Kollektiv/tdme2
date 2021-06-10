#include <tdme/tools/editor/controllers/ContextMenuScreenController.h>

#include <string>

#include <tdme/engine/Engine.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIMultilineTextNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

using std::string;

using tdme::engine::Engine;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIMultilineTextNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINode_RequestedConstraints;
using tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::gui::GUIParser;
using tdme::tools::editor::controllers::ContextMenuScreenController;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::MutableString;
using tdme::utilities::StringTools;

ContextMenuScreenController::ContextMenuScreenController()
{
}

ContextMenuScreenController::~ContextMenuScreenController()
{
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
		screenNode->setVisible(false);
		screenNode->addActionListener(this);
		screenNode->addFocusListener(this);
		contextMenuNode = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("contextmenu"));
	} catch (Exception& exception) {
		Console::print(string("ContextMenuScreenController::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

void ContextMenuScreenController::dispose()
{
}

void ContextMenuScreenController::show(int mouseX, int mouseY)
{
	auto x = static_cast<int>((float)mouseX * (float)screenNode->getScreenWidth() / (float)Engine::getInstance()->getGUI()->getWidth());
	auto y = static_cast<int>((float)mouseY * (float)screenNode->getScreenHeight() / (float)Engine::getInstance()->getGUI()->getHeight());
	contextMenuNode->getRequestsConstraints().leftType = GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL;
	contextMenuNode->getRequestsConstraints().left = x;
	contextMenuNode->getRequestsConstraints().topType = GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL;
	contextMenuNode->getRequestsConstraints().top = y;
	screenNode->setVisible(true);
	screenNode->layout();
	Engine::getInstance()->getGUI()->setFoccussedNode(contextMenuNode);
}

void ContextMenuScreenController::close()
{
	screenNode->setVisible(false);
}

void ContextMenuScreenController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node)
{
	Console::println("ContextMenuScreenController::onActionPerformed(): " + node->getId());
}

void ContextMenuScreenController::onFocus(GUIElementNode* node) {
	if (screenNode->isVisible() == true && node->getId() == "background") close();
}

void ContextMenuScreenController::onUnfocus(GUIElementNode* node) {
}

void ContextMenuScreenController::clear() {
	required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(contextMenuNode->getId()))->clearSubNodes();
}

void ContextMenuScreenController::addMenuItem(const string& text, const string& id) {
	required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(contextMenuNode->getId()))->addSubNodes(
		"<context-menu-item text=\"" + GUIParser::escapeQuotes(text) + "\" id=\"" + GUIParser::escapeQuotes(id) + "\" />",
		true
	);
}

void ContextMenuScreenController::addMenuSeparator() {
	required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(contextMenuNode->getId()))->addSubNodes(
		"<menu-separator />",
		true
	);
}
