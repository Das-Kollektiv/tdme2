#include <tdme/tools/editor/controllers/FindReplaceDialogScreenController.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Version.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUIStyledTextNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

using std::string;

using tdme::application::Application;
using tdme::engine::Engine;
using tdme::engine::Version;
using tdme::gui::events::GUIActionListenerType;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUIStyledTextNode;
using tdme::gui::nodes::GUITextNode;
using tdme::gui::GUIParser;
using tdme::tools::editor::controllers::FindReplaceDialogScreenController;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::MutableString;
using tdme::utilities::StringTools;

FindReplaceDialogScreenController::FindReplaceDialogScreenController()
{
}

FindReplaceDialogScreenController::~FindReplaceDialogScreenController()
{
	screenNode = nullptr;
}

GUIScreenNode* FindReplaceDialogScreenController::getScreenNode()
{
	return screenNode;
}

void FindReplaceDialogScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse("resources/engine/gui", "popup_findreplace.xml");
		screenNode->setVisible(false);
		screenNode->addActionListener(this);
		findText = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("findreplace_findtext"));
		replaceText = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("findreplace_replacetext"));
		matchCase = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("findreplace_matchcase"));
		wholeWordOnly = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("findreplace_wholewordonly"));
		inSelectionOnly = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("findreplace_inselectiononly"));
		findButton = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("findreplace_find"));
		countButton = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("findreplace_count"));
		cancelButton = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("findreplace_cancel"));
		replaceButton = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("findreplace_replace"));
		replaceButtonAll = required_dynamic_cast<GUIElementNode*>(screenNode->getNodeById("findreplace_replaceall"));
	} catch (Exception& exception) {
		Console::print(string("FindReplaceDialogScreenController::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

void FindReplaceDialogScreenController::dispose()
{
}

void FindReplaceDialogScreenController::show()
{
	screenNode->setVisible(true);
}

void FindReplaceDialogScreenController::close()
{
	screenNode->setVisible(false);
}

void FindReplaceDialogScreenController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node)
{
	if (type == GUIActionListenerType::PERFORMED) {
		if (StringTools::startsWith(node->getId(), "findreplace_caption_close_") == true) { // TODO: a.drewke, check with DH) {
			close();
		}
	}
}
