#include <tdme/tools/editor/controllers/SelectorDialogScreenController.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Version.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/events/GUIFocusListener.h>
#include <tdme/gui/events/GUITooltipRequestListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUIStyledTextNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/tools/editor/controllers/TooltipScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

using std::string;

using tdme::application::Application;
using tdme::engine::Engine;
using tdme::engine::Version;
using tdme::gui::events::GUIActionListener;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::events::GUIFocusListener;
using tdme::gui::events::GUITooltipRequestListener;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUIStyledTextNode;
using tdme::gui::nodes::GUITextNode;
using tdme::gui::GUIParser;
using tdme::gui::GUI;
using tdme::tools::editor::controllers::SelectorDialogScreenController;
using tdme::tools::editor::controllers::TooltipScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::MutableString;
using tdme::utilities::StringTools;

SelectorDialogScreenController::SelectorDialogScreenController(PopUps* popUps): popUps(popUps)
{
}

SelectorDialogScreenController::~SelectorDialogScreenController()
{
	screenNode = nullptr;
}

GUIScreenNode* SelectorDialogScreenController::getScreenNode()
{
	return screenNode;
}

void SelectorDialogScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse("resources/engine/gui", "popup_selector.xml");
		screenNode->setEnabled(false);
		screenNode->addActionListener(this);
		screenNode->addTooltipRequestListener(this);
		screenNode->invalidateLayouts();
	} catch (Exception& exception) {
		Console::printLine("SelectorDialogScreenController::initialize(): An error occurred: " + string(exception.what()));
	}
}

void SelectorDialogScreenController::dispose()
{
}

void SelectorDialogScreenController::show()
{
	screenNode->setEnabled(true);
}

void SelectorDialogScreenController::close()
{
	screenNode->setEnabled(false);
}

void SelectorDialogScreenController::onAction(GUIActionListenerType type, GUIElementNode* node)
{
	if (type == GUIActionListenerType::PERFORMED) {
		if (StringTools::startsWith(node->getId(), "tab_selector_close_") == true) { // TODO: a.drewke, check with DH) {
			close();
		}
	}
}

void SelectorDialogScreenController::onFocus(GUIElementNode* node) {
	GUI::setDisableTabFocusControl(node->getScreenNode() != screenNode);
}

void SelectorDialogScreenController::onUnfocus(GUIElementNode* node) {
}

void SelectorDialogScreenController::onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) {
	popUps->getTooltipScreenController()->show(mouseX, mouseY, node->getToolTip());
}

void SelectorDialogScreenController::onTooltipCloseRequest() {
	popUps->getTooltipScreenController()->close();
}
