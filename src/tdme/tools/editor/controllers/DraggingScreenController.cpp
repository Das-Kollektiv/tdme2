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
		screenNode->setVisible(false);
		GUINode::dumpNode(screenNode);
		draggableNode = required_dynamic_cast<GUIParentNode*>(screenNode->getNodeById("draggable"));
			} catch (Exception& exception) {
		Console::print(string("DraggingScreenController::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

void DraggingScreenController::dispose()
{
}

void DraggingScreenController::onMove(GUINode* node) {
}

void DraggingScreenController::onRelease(GUINode* node, int mouseX, int mouseY) {
	Console::println("DraggingScreenController::onRelease(): " + node->getId() + ", x: " + to_string(mouseX) + ", y: " + to_string(mouseY));
	close();
}

void DraggingScreenController::start(int mouseX, int mouseY, const string& xml)
{
	//
	try {
		draggableNode->replaceSubNodes(xml, true);
	} catch (Exception& exception) {
		Console::print(string("DraggingScreenController::start(): An error occurred: "));
		Console::println(string(exception.what()));
	}
	auto x = static_cast<int>((float)(mouseX - draggableNode->getContentWidth() / 2) * (float)screenNode->getScreenWidth() / (float)Engine::getInstance()->getGUI()->getWidth());
	auto y = static_cast<int>((float)(mouseY - draggableNode->getContentHeight() / 2) * (float)screenNode->getScreenHeight() / (float)Engine::getInstance()->getGUI()->getHeight());
	x = Math::min(x, screenNode->getScreenWidth() - draggableNode->getContentWidth());
	y = Math::min(y, screenNode->getScreenHeight() - draggableNode->getContentHeight());
	draggableNode->getRequestsConstraints().leftType = GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL;
	draggableNode->getRequestsConstraints().left = x;
	draggableNode->getRequestsConstraints().topType = GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL;
	draggableNode->getRequestsConstraints().top = y;
	screenNode->setVisible(true);
	screenNode->layout();
	//
	Engine::getInstance()->getGUI()->startMouseDragging(draggableNode);
	//
	try {
		((GUIMoveableController*)(draggableNode->getController()))->startMoving();
	} catch (Exception& exception) {
		Console::print(string("DraggingScreenController::start(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

void DraggingScreenController::close()
{
	screenNode->setVisible(false);
}
