#include <tdme/tools/editor/controllers/TooltipScreenController.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints.h>
#include <tdme/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/math/Math.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

using tdme::tools::editor::controllers::TooltipScreenController;

using std::string;
using std::unordered_map;

using tdme::engine::Engine;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINode_RequestedConstraints;
using tdme::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUIStyledTextNode;
using tdme::gui::nodes::GUITextNode;
using tdme::gui::GUIParser;
using tdme::math::Math;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::MutableString;
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
		screenNode->setVisible(false);
		tooltipNode = required_dynamic_cast<GUITextNode*>(screenNode->getNodeById("tooltip"));
	} catch (Exception& exception) {
		Console::print(string("TooltipScreenController::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

void TooltipScreenController::dispose()
{
}

void TooltipScreenController::show(int mouseX, int mouseY, const string& tooltip)
{
	auto x = static_cast<int>((float)mouseX * (float)screenNode->getScreenWidth() / (float)Engine::getInstance()->getGUI()->getWidth());
	auto y = static_cast<int>((float)mouseY * (float)screenNode->getScreenHeight() / (float)Engine::getInstance()->getGUI()->getHeight());
	tooltipNode->setText(MutableString(tooltip));
	x = Math::min(x, screenNode->getScreenWidth() - tooltipNode->getContentWidth());
	y = Math::min(y, screenNode->getScreenHeight() - tooltipNode->getContentHeight());
	tooltipNode->getRequestsConstraints().leftType = GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL;
	tooltipNode->getRequestsConstraints().left = x;
	tooltipNode->getRequestsConstraints().topType = GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL;
	tooltipNode->getRequestsConstraints().top = y;
	screenNode->setVisible(true);
	screenNode->layout();
}

void TooltipScreenController::close()
{
	screenNode->setVisible(false);
}
