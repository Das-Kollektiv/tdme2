#include <tdme/tools/editor/controllers/AboutDialogScreenController.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Version.h>
#include <tdme/gui/events/GUIActionListener.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIMultilineTextNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
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
using tdme::gui::nodes::GUIMultilineTextNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::gui::GUIParser;
using tdme::tools::editor::controllers::AboutDialogScreenController;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::MutableString;
using tdme::utilities::StringTools;

AboutDialogScreenController::AboutDialogScreenController()
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
		screenNode->setVisible(false);
		screenNode->addActionListener(this);
		required_dynamic_cast<GUITextNode*>(screenNode->getNodeById("about_version"))->setText(MutableString(Version::getVersion()));
		required_dynamic_cast<GUITextNode*>(screenNode->getNodeById("about_platform"))->setText(MutableString("Platform: " + Application::getOSName() + "/" + Application::getCPUName()));
		required_dynamic_cast<GUIMultilineTextNode*>(screenNode->getNodeById("about_graphics"))->setText(MutableString("Graphics: " + Engine::getInstance()->getGraphicsRenderer() + " abc, bef, hans, julian, bernd, graphifckarten und penisse und bernsteinzimmer. kross"));
	} catch (Exception& exception) {
		Console::print(string("AboutDialogScreenController::initialize(): An error occurred: "));
		Console::println(string(exception.what()));
	}
}

void AboutDialogScreenController::dispose()
{
}

void AboutDialogScreenController::show()
{
	screenNode->setVisible(true);
	screenNode->layout();
}

void AboutDialogScreenController::close()
{
	screenNode->setVisible(false);
}

void AboutDialogScreenController::onActionPerformed(GUIActionListenerType type, GUIElementNode* node)
{
	if (type == GUIActionListenerType::PERFORMED) {
		if (StringTools::startsWith(node->getId(), "about_caption_close_") == true) { // TODO: a.drewke, check with DH) {
			close();
		}
	}
}
