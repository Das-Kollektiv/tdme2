#include <tdme/tools/editor/controllers/AboutDialogScreenController.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Version.h>
#include <agui/gui/events/GUIActionListener.h>
#include <agui/gui/events/GUIFocusListener.h>
#include <agui/gui/events/GUITooltipRequestListener.h>
#include <agui/gui/nodes/GUIElementNode.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/nodes/GUIStyledTextNode.h>
#include <agui/gui/nodes/GUITextNode.h>
#include <agui/gui/GUI.h>
#include <agui/gui/GUIParser.h>
#include <tdme/tools/editor/controllers/TooltipScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <agui/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

using std::string;

using tdme::application::Application;
using tdme::engine::Engine;
using tdme::engine::Version;
using agui::gui::events::GUIActionListener;
using agui::gui::events::GUIActionListenerType;
using agui::gui::events::GUIFocusListener;
using agui::gui::events::GUITooltipRequestListener;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::nodes::GUIStyledTextNode;
using agui::gui::nodes::GUITextNode;
using agui::gui::GUIParser;
using agui::gui::GUI;
using tdme::tools::editor::controllers::AboutDialogScreenController;
using tdme::tools::editor::controllers::TooltipScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using agui::utilities::MutableString;
using tdme::utilities::StringTools;

AboutDialogScreenController::AboutDialogScreenController(PopUps* popUps): popUps(popUps)
{
}

AboutDialogScreenController::~AboutDialogScreenController()
{
	screenNode = nullptr;
}

GUIScreenNode* AboutDialogScreenController::getScreenNode()
{
	return screenNode;
}

void AboutDialogScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse("resources/engine/gui", "popup_about.xml");
		screenNode->setEnabled(false);
		screenNode->addActionListener(this);
		screenNode->addTooltipRequestListener(this);
		required_dynamic_cast<GUITextNode*>(screenNode->getNodeById("about_version"))->setText(MutableString(Version::getVersion()));
		required_dynamic_cast<GUITextNode*>(screenNode->getNodeById("about_platform"))->setText(MutableString("Platform: " + Application::getOSName() + "/" + Application::getCPUName()));
		required_dynamic_cast<GUIStyledTextNode*>(screenNode->getNodeById("about_graphics"))->setText(MutableString("Graphics: " + StringTools::replace(StringTools::replace(Engine::getInstance()->getGraphicsRenderer(), "[", "\\["), "]", "\\]")));
		screenNode->invalidateLayouts();
	} catch (Exception& exception) {
		Console::printLine("AboutDialogScreenController::initialize(): An error occurred: " + string(exception.what()));
	}
}

void AboutDialogScreenController::dispose()
{
}

void AboutDialogScreenController::show()
{
	screenNode->setEnabled(true);
}

void AboutDialogScreenController::close()
{
	screenNode->setEnabled(false);
}

void AboutDialogScreenController::onAction(GUIActionListenerType type, GUIElementNode* node)
{
	if (type == GUIActionListenerType::PERFORMED) {
		if (StringTools::startsWith(node->getId(), "about_caption_close_") == true) { // TODO: a.drewke, check with DH) {
			close();
		}
	}
}

void AboutDialogScreenController::onFocus(GUIElementNode* node) {
	GUI::setDisableTabFocusControl(node->getScreenNode() != screenNode);
}

void AboutDialogScreenController::onUnfocus(GUIElementNode* node) {
}

void AboutDialogScreenController::onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) {
	popUps->getTooltipScreenController()->show(mouseX, mouseY, node->getToolTip());
}

void AboutDialogScreenController::onTooltipCloseRequest() {
	popUps->getTooltipScreenController()->close();
}
