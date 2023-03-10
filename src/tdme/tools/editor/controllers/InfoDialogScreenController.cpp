#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
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

using tdme::tools::editor::controllers::InfoDialogScreenController;

using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUIStyledTextNode;
using tdme::gui::nodes::GUITextNode;
using tdme::gui::GUIParser;
using tdme::tools::editor::controllers::TooltipScreenController;
using tdme::tools::editor::misc::PopUps;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::MutableString;
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
		Console::println("InfoDialogScreenController::initialize(): An error occurred: " + string(exception.what()));
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
