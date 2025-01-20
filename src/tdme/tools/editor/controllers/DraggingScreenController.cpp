#include <tdme/tools/editor/controllers/DraggingScreenController.h>

#include <memory>
#include <string>

#include <agui/agui.h>
#include <agui/gui/elements/GUIMoveableController.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUINode_RequestedConstraints.h>
#include <agui/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>
#include <agui/gui/nodes/GUIParentNode.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/GUI.h>
#include <agui/gui/GUIParser.h>
#include <agui/utilities/MutableString.h>

#include <tdme/tdme.h>
#include <tdme/engine/Engine.h>
#include <tdme/math/Math.h>
#include <tdme/utilities/Action.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/StringTools.h>

using tdme::tools::editor::controllers::DraggingScreenController;

using std::string;
using std::to_string;
using std::unique_ptr;
using std::unordered_map;

using agui::gui::elements::GUIMoveableController;
using agui::gui::events::GUIActionListenerType;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINode_RequestedConstraints;
using agui::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using agui::gui::nodes::GUIParentNode;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::GUIParser;
using agui::utilities::MutableString;

using tdme::engine::Engine;
using tdme::math::Math;
using tdme::utilities::Action;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::StringTools;

DraggingScreenController::DraggingScreenController()
{
}

DraggingScreenController::~DraggingScreenController()
{
	screenNode = nullptr;
}

GUIScreenNode* DraggingScreenController::getScreenNode()
{
	return screenNode;
}

void DraggingScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse("resources/engine/gui", "popup_dragging.xml");
		screenNode->addMoveListener(this);
		screenNode->setEnabled(false);
		draggableNode = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("draggable"));
	} catch (Exception& exception) {
		Console::printLine("DraggingScreenController::initialize(): An error occurred: " + string(exception.what()));
	}
}

void DraggingScreenController::dispose()
{
}

bool DraggingScreenController::accept(GUINode* node) {
	return true;
}

void DraggingScreenController::onMove(GUINode* node) {
}

void DraggingScreenController::onRelease(GUINode* node, int mouseX, int mouseY) {
	dragReleaseMouseX = mouseX;
	dragReleaseMouseY = mouseY;
	close();
	if (onReleaseAction != nullptr) {
		onReleaseAction->performAction();
		onReleaseAction = nullptr;
	}
}

void DraggingScreenController::start(int mouseX, int mouseY, const string& xml, const string& payload, Action* onReleaseAction)
{
	this->payload = payload;
	this->onReleaseAction = unique_ptr<Action>(onReleaseAction);
	dragReleaseMouseX = -1;
	dragReleaseMouseY = -1;
	//
	try {
		draggableNode->replaceSubNodes(xml, true);
	} catch (Exception& exception) {
		Console::printLine("DraggingScreenController::start(): An error occurred: " + string(exception.what()));
	}
	auto scaledMouseX = Engine::getInstance()->getGUI()->getScaledX(screenNode, mouseX);
	auto scaledMouseY = Engine::getInstance()->getGUI()->getScaledY(screenNode, mouseY);
	auto scaledX = Engine::getInstance()->getGUI()->getScaledX(screenNode, mouseX - draggableNode->getContentWidth() / 2);
	auto scaledY = Engine::getInstance()->getGUI()->getScaledY(screenNode, mouseY - draggableNode->getContentHeight() / 2);
	scaledX = Math::min(scaledX, screenNode->getScreenWidth() - draggableNode->getContentWidth());
	scaledY = Math::min(scaledY, screenNode->getScreenHeight() - draggableNode->getContentHeight());
	draggableNode->getRequestsConstraints().leftType = GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL;
	draggableNode->getRequestsConstraints().left = scaledX;
	draggableNode->getRequestsConstraints().topType = GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL;
	draggableNode->getRequestsConstraints().top = scaledY;
	screenNode->setEnabled(true);
	screenNode->layout();
	//
	Engine::getInstance()->getGUI()->startMouseDragging(draggableNode);
	//
	try {
		((GUIMoveableController*)(draggableNode->getController()))->startMoving(scaledMouseX, scaledMouseY);
	} catch (Exception& exception) {
		Console::printLine("DraggingScreenController::start(): An error occurred: " + string(exception.what()));
	}
}

void DraggingScreenController::close()
{
	screenNode->setEnabled(false);
}
