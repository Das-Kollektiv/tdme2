#include <tdme/tools/shared/controller/InfoDialogScreenController.h>

#include <string>

#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIMultilineTextNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

using std::string;

using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIMultilineTextNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::gui::GUIParser;
using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::MutableString;
using tdme::utilities::StringTools;

InfoDialogScreenController::InfoDialogScreenController()
{
}

GUIScreenNode* InfoDialogScreenController::getScreenNode()
{
	return screenNode;
}

void InfoDialogScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse("resources/engine/gui", "popup_infodialog.xml");
		screenNode->setVisible(false);
		screenNode->addActionListener(this);
		tabsHeaderNode = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("infodialog_tabs-header"));
		messageNode = dynamic_cast< GUIMultilineTextNode* >(screenNode->getNodeById("infodialog_message"));
	} catch (Exception& exception) {
		Console::print(string("InfoDialogScreenController::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

void InfoDialogScreenController::dispose()
{
	screenNode = nullptr;
}

void InfoDialogScreenController::show(const string& caption, const string& message)
{
	screenNode->setVisible(true);
	required_dynamic_cast<GUIParentNode*>(screenNode->getInnerNodeById(tabsHeaderNode->getId()))->replaceSubNodes("<tab id=\"infodialog_caption\" image=\"resources/engine/images/attention.png\" text=\"" + caption + "\" closeable=\"true\"/>", true);
	messageNode->setText(message);
	screenNode->layout();
}

void InfoDialogScreenController::close()
{
	screenNode->setVisible(false);
}

void InfoDialogScreenController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node)
{
	if (type == GUIActionListenerType::PERFORMED) {
		if (node->getId() == "infodialog_button1" ||
			StringTools::startsWith(node->getId(), "infodialog_caption_close_") == true) { // TODO: a.drewke, check with DH) {
			close();
		}
	}
}
