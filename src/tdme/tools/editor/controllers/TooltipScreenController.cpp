#include <tdme/tools/editor/controllers/TooltipScreenController.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/Engine.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUINode_RequestedConstraints.h>
#include <agui/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/nodes/GUITextNode.h>
#include <agui/gui/GUI.h>
#include <agui/gui/GUIParser.h>
#include <tdme/math/Math.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <agui/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

using tdme::tools::editor::controllers::TooltipScreenController;

using std::string;
using std::unordered_map;

using tdme::engine::Engine;
using agui::gui::events::GUIActionListenerType;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINode_RequestedConstraints;
using agui::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::nodes::GUITextNode;
using agui::gui::GUIParser;
using tdme::math::Math;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using agui::utilities::MutableString;
using tdme::utilities::StringTools;

TooltipScreenController::TooltipScreenController()
{
}

TooltipScreenController::~TooltipScreenController()
{
	screenNode = nullptr;
}

GUIScreenNode* TooltipScreenController::getScreenNode()
{
	return screenNode;
}

void TooltipScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse("resources/engine/gui", "popup_tooltip.xml");
		screenNode->setEnabled(false);
		tooltipNode = required_dynamic_cast<GUITextNode*>(screenNode->getNodeById("tooltip"));
	} catch (Exception& exception) {
		Console::printLine("TooltipScreenController::initialize(): An error occurred: " + string(exception.what()));
	}
}

void TooltipScreenController::dispose()
{
}

void TooltipScreenController::show(int mouseX, int mouseY, const string& tooltip)
{
	auto scaledX = Engine::getInstance()->getGUI()->getScaledX(screenNode, mouseX);
	auto scaledY = Engine::getInstance()->getGUI()->getScaledY(screenNode, mouseY + tooltipNode->getContentHeight() / 2);
	scaledX = Math::min(scaledX, screenNode->getScreenWidth() - tooltipNode->getContentWidth());
	scaledY = Math::min(scaledY, screenNode->getScreenHeight() - tooltipNode->getContentHeight());
	tooltipNode->setText(MutableString(tooltip));
	tooltipNode->getRequestsConstraints().leftType = GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL;
	tooltipNode->getRequestsConstraints().left = scaledX;
	tooltipNode->getRequestsConstraints().topType = GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL;
	tooltipNode->getRequestsConstraints().top = scaledY;
	screenNode->setEnabled(true);
	screenNode->layout();
}

void TooltipScreenController::close()
{
	screenNode->setEnabled(false);
}
