#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>

#include <string>

#include <tdme/tdme.h>
#include <agui/gui/events/GUIActionListener.h>
#include <agui/gui/nodes/GUIElementNode.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUIParentNode.h>
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

using tdme::tools::editor::controllers::InfoDialogScreenController;

using agui::gui::events::GUIActionListenerType;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUIParentNode;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::nodes::GUIStyledTextNode;
using agui::gui::nodes::GUITextNode;
using agui::gui::GUI;
using agui::gui::GUIParser;
using tdme::tools::editor::controllers::TooltipScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using agui::utilities::MutableString;
using tdme::utilities::StringTools;

InfoDialogScreenController::InfoDialogScreenController(PopUps* popUps): popUps(popUps)
{
}

InfoDialogScreenController::~InfoDialogScreenController()
{
	screenNode = nullptr;
}

GUIScreenNode* InfoDialogScreenController::getScreenNode()
{
	return screenNode;
}

void InfoDialogScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse("resources/engine/gui", "popup_infodialog.xml");
		screenNode->setEnabled(false);
		screenNode->addActionListener(this);
		screenNode->addTooltipRequestListener(this);
		tabsHeaderNode = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("infodialog_tabs-header"));
		messageNode = dynamic_cast<GUIStyledTextNode*>(screenNode->getNodeById("infodialog_message"));
	} catch (Exception& exception) {
		Console::printLine("InfoDialogScreenController::initialize(): An error occurred: " + string(exception.what()));
	}
}

void InfoDialogScreenController::dispose()
{
}

void InfoDialogScreenController::show(const string& caption, const string& message)
{
	screenNode->setEnabled(true);
	required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(tabsHeaderNode->getId()))->replaceSubNodes("<tab id=\"infodialog_caption\" image=\"resources/engine/images/attention.png\" text=\"" + caption + "\" closeable=\"true\"/>", true);
	messageNode->setText(message);
}

void InfoDialogScreenController::close()
{
	screenNode->setEnabled(false);
}

void InfoDialogScreenController::onAction(GUIActionListenerType type, GUIElementNode* node)
{
	if (type == GUIActionListenerType::PERFORMED) {
		if (node->getId() == "infodialog_button1" ||
			StringTools::startsWith(node->getId(), "infodialog_caption_close_") == true) { // TODO: a.drewke, check with DH) {
			close();
		}
	}
}

void InfoDialogScreenController::onFocus(GUIElementNode* node) {
	GUI::setDisableTabFocusControl(node->getScreenNode() != screenNode);
}

void InfoDialogScreenController::onUnfocus(GUIElementNode* node) {
}

void InfoDialogScreenController::onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) {
	popUps->getTooltipScreenController()->show(mouseX, mouseY, node->getToolTip());
}

void InfoDialogScreenController::onTooltipCloseRequest() {
	popUps->getTooltipScreenController()->close();
}
