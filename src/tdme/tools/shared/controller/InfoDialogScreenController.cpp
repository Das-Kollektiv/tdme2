#include <tdme/tools/shared/controller/InfoDialogScreenController.h>

#include <string>

#include <tdme/gui/GUIParser.h>
#include <tdme/gui/events/GUIActionListener_Type.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIMultilineTextNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>

using std::string;

using tdme::tools::shared::controller::InfoDialogScreenController;
using tdme::gui::GUIParser;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIMultilineTextNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::utils::Console;
using tdme::utils::Exception;
using tdme::utils::MutableString;

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
		screenNode = GUIParser::parse("resources/engine/tools/shared/gui", "infodialog.xml");
		screenNode->setVisible(false);
		screenNode->addActionListener(this);
		captionNode = dynamic_cast< GUITextNode* >(screenNode->getNodeById("infodialog_caption"));
		messageNode = dynamic_cast< GUIMultilineTextNode* >(screenNode->getNodeById("infodialog_message"));
	} catch (Exception& exception) {
		Console::print(string("InfoDialogScreenController::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

void InfoDialogScreenController::dispose()
{
}

void InfoDialogScreenController::show(const string& caption, const string& message)
{
	screenNode->setVisible(true);
	captionNode->setText(caption);
	messageNode->setText(message);
	screenNode->layout();
}

void InfoDialogScreenController::close()
{
	screenNode->setVisible(false);
}

void InfoDialogScreenController::onActionPerformed(GUIActionListener_Type* type, GUIElementNode* node)
{
	{
		auto v = type;
		if (v == GUIActionListener_Type::PERFORMED) {
			if (node->getId().compare("infodialog_ok") == 0) {
				close();
			}
		}
	}
}
