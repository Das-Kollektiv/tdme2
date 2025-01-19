#include <tdme/tools/editor/controllers/ProgressBarScreenController.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/Engine.h>
#include <agui/gui/nodes/GUIElementNode.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/nodes/GUITextNode.h>
#include <agui/gui/GUI.h>
#include <agui/gui/GUIParser.h>
#include <tdme/tools/editor/controllers/TooltipScreenController.h>
#include <tdme/tools/editor/misc/PopUps.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <agui/utilities/MutableString.h>

using std::string;

using tdme::tools::editor::controllers::ProgressBarScreenController;

using tdme::application::Application;
using tdme::engine::Engine;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINodeController;
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

ProgressBarScreenController::ProgressBarScreenController(PopUps* popUps): popUps(popUps)
{
}

ProgressBarScreenController::~ProgressBarScreenController() {
}

GUIScreenNode* ProgressBarScreenController::getScreenNode()
{
	return screenNode;
}

void ProgressBarScreenController::initialize()
{
	try {
		screenNode = GUIParser::parse("resources/engine/gui", "popup_progressbar.xml");
		screenNode->addTooltipRequestListener(this);
		screenNode->setEnabled(false);
		progressBarNode = dynamic_cast<GUIElementNode*>(screenNode->getNodeById("progressbar"));
		progressBarParent = dynamic_cast<GUIElementNode*>(screenNode->getNodeById("progressbar_parent"));
		progressMessageNode = dynamic_cast<GUITextNode*>(screenNode->getNodeById("progress_message"));
	} catch (Exception& exception) {
		Console::printLine("ProgressBarScreenController::initialize(): An error occurred: " + string(exception.what()));
	}
}

void ProgressBarScreenController::dispose()
{
	screenNode = nullptr;
}

void ProgressBarScreenController::show(const string& message, bool showProgressBar)
{
	progressMessageNode->setText(MutableString(message));
	if (showProgressBar == true) {
		progressBarParent->getActiveConditions().add("show-progressbar");
	} else {
		progressBarParent->getActiveConditions().remove("show-progressbar");
	}
	screenNode->setEnabled(true);
	progress2(0.0f);
}

void ProgressBarScreenController::progress(float value) {
	progressBarNode->getController()->setValue(MutableString(value, 4));
	Engine::getInstance()->display();
	Engine::getInstance()->getGUI()->render();
	Engine::getInstance()->getGUI()->handleEvents();
	Application::swapBuffers();
}

void ProgressBarScreenController::progress2(float value) {
	progressBarNode->getController()->setValue(MutableString(value, 4));
}

void ProgressBarScreenController::close()
{
	screenNode->setEnabled(false);
}

void ProgressBarScreenController::onTooltipShowRequest(GUINode* node, int mouseX, int mouseY) {
	popUps->getTooltipScreenController()->show(mouseX, mouseY, node->getToolTip());
}

void ProgressBarScreenController::onTooltipCloseRequest() {
	popUps->getTooltipScreenController()->close();
}
