#include <tdme/tools/editor/controllers/DraggingScreenController.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/elements/GUIMoveableController.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/math/Math.h>
#include <tdme/utilities/Action.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

using tdme::tools::editor::controllers::DraggingScreenController;

using std::string;
using std::to_string;
using std::unordered_map;

using tdme::engine::Engine;
using tdme::gui::elements::GUIMoveableController;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINode_RequestedConstraints;
using tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUIParser;
using tdme::math::Math;
using tdme::utilities::Action;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::MutableString;
using tdme::utilities::StringTools;

DraggingScreenController::DraggingScreenController()
{
}

DraggingScreenController::~DraggingScreenController()
{
	screenNode = nullptr;
	if (onReleaseAction != nullptr) delete onReleaseAction;
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
		Console::println("DraggingScreenController::initialize(): An error occurred: " + string(exception.what()));
	}
}

void DraggingScreenController::dispose()
{
}

void DraggingScreenController::onMove(GUINode* node) {
}

void DraggingScreenController::onRelease(GUINode* node, int mouseX, int mouseY) {
	dragReleaseMouseX = mouseX;
	dragReleaseMouseY = mouseY;
	close();
	if (onReleaseAction != nullptr) {
		onReleaseAction->performAction();
		delete onReleaseAction;
		onReleaseAction = nullptr;
	}
}

void DraggingScreenController::start(int mouseX, int mouseY, const string& xml, const string& payload, Action* onReleaseAction)
{
	this->payload = payload;
	if (this->onReleaseAction != nullptr) delete this->onReleaseAction;
	this->onReleaseAction = onReleaseAction;
	dragReleaseMouseX = -1;
	dragReleaseMouseY = -1;
	//
	try {
		draggableNode->replaceSubNodes(xml, true);
	} catch (Exception& exception) {
		Console::println("DraggingScreenController::start(): An error occurred: " + string(exception.what()));
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
		Console::println("DraggingScreenController::start(): An error occurred: " + string(exception.what()));
	}
}

void DraggingScreenController::close()
{
	screenNode->setEnabled(false);
}
