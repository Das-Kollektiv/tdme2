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
