#include <tdme/tools/editor/misc/PopUps.h>

#include <tdme/tdme.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/tools/editor/controllers/AboutDialogScreenController.h>
#include <tdme/tools/editor/controllers/ColorPickerScreenController.h>
#include <tdme/tools/editor/controllers/ContextMenuScreenController.h>
#include <tdme/tools/editor/controllers/FileDialogScreenController.h>
#include <tdme/tools/editor/controllers/FindReplaceDialogScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/controllers/ProgressBarScreenController.h>

using tdme::engine::Engine;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUI;
using tdme::tools::editor::controllers::AboutDialogScreenController;
using tdme::tools::editor::controllers::ColorPickerScreenController;
using tdme::tools::editor::controllers::ContextMenuScreenController;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::FindReplaceDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::controllers::ProgressBarScreenController;
using tdme::tools::editor::misc::PopUps;

PopUps::PopUps()
{
	fileDialogScreenController = new FileDialogScreenController();
	infoDialogScreenController = new InfoDialogScreenController();
	aboutDialogScreenController = new AboutDialogScreenController();
	progressBarScreenController = new ProgressBarScreenController();
	colorPickerScreenController = new ColorPickerScreenController();
	contextMenuScreenController = new ContextMenuScreenController();
	findReplaceDialogScreenController = new FindReplaceDialogScreenController();
}

PopUps::~PopUps() {
	delete fileDialogScreenController;
	delete infoDialogScreenController;
	delete aboutDialogScreenController;
	delete progressBarScreenController;
	delete colorPickerScreenController;
	delete contextMenuScreenController;
	delete findReplaceDialogScreenController;
}

void PopUps::initialize()
{
	fileDialogScreenController->initialize();
	infoDialogScreenController->initialize();
	aboutDialogScreenController->initialize();
	progressBarScreenController->initialize();
	colorPickerScreenController->initialize();
	contextMenuScreenController->initialize();
	findReplaceDialogScreenController->initialize();
	Engine::getInstance()->getGUI()->addScreen(aboutDialogScreenController->getScreenNode()->getId(), aboutDialogScreenController->getScreenNode());
	Engine::getInstance()->getGUI()->addScreen(colorPickerScreenController->getScreenNode()->getId(), colorPickerScreenController->getScreenNode());
	Engine::getInstance()->getGUI()->addScreen(fileDialogScreenController->getScreenNode()->getId(), fileDialogScreenController->getScreenNode());
	Engine::getInstance()->getGUI()->addScreen(findReplaceDialogScreenController->getScreenNode()->getId(), findReplaceDialogScreenController->getScreenNode());
	Engine::getInstance()->getGUI()->addScreen(contextMenuScreenController->getScreenNode()->getId(), contextMenuScreenController->getScreenNode());
	Engine::getInstance()->getGUI()->addScreen(infoDialogScreenController->getScreenNode()->getId(), infoDialogScreenController->getScreenNode());
	Engine::getInstance()->getGUI()->addScreen(progressBarScreenController->getScreenNode()->getId(), progressBarScreenController->getScreenNode());
}

void PopUps::dispose()
{
	Engine::getInstance()->getGUI()->removeScreen(aboutDialogScreenController->getScreenNode()->getId());
	Engine::getInstance()->getGUI()->removeScreen(colorPickerScreenController->getScreenNode()->getId());
	Engine::getInstance()->getGUI()->removeScreen(fileDialogScreenController->getScreenNode()->getId());
	Engine::getInstance()->getGUI()->removeScreen(findReplaceDialogScreenController->getScreenNode()->getId());
	Engine::getInstance()->getGUI()->removeScreen(contextMenuScreenController->getScreenNode()->getId());
	Engine::getInstance()->getGUI()->removeScreen(infoDialogScreenController->getScreenNode()->getId());
	Engine::getInstance()->getGUI()->removeScreen(progressBarScreenController->getScreenNode()->getId());
	fileDialogScreenController->dispose();
	infoDialogScreenController->dispose();
	aboutDialogScreenController->dispose();
	progressBarScreenController->dispose();
	colorPickerScreenController->dispose();
	contextMenuScreenController->dispose();
	findReplaceDialogScreenController->dispose();
}
