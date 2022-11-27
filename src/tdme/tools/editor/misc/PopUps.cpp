#include <tdme/tools/editor/misc/PopUps.h>

#include <tdme/tdme.h>
#include <tdme/engine/Engine.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/tools/editor/controllers/AboutDialogScreenController.h>
#include <tdme/tools/editor/controllers/ColorPickerScreenController.h>
#include <tdme/tools/editor/controllers/ContextMenuScreenController.h>
#include <tdme/tools/editor/controllers/DraggingScreenController.h>
#include <tdme/tools/editor/controllers/FileDialogScreenController.h>
#include <tdme/tools/editor/controllers/FindReplaceDialogScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/controllers/ProgressBarScreenController.h>
#include <tdme/tools/editor/controllers/TooltipScreenController.h>

using tdme::engine::Engine;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUI;
using tdme::tools::editor::controllers::AboutDialogScreenController;
using tdme::tools::editor::controllers::ColorPickerScreenController;
using tdme::tools::editor::controllers::ContextMenuScreenController;
using tdme::tools::editor::controllers::DraggingScreenController;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::FindReplaceDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::controllers::ProgressBarScreenController;
using tdme::tools::editor::controllers::TooltipScreenController;
using tdme::tools::editor::misc::PopUps;

PopUps::PopUps()
{
	fileDialogScreenController = new FileDialogScreenController(this);
	infoDialogScreenController = new InfoDialogScreenController(this);
	aboutDialogScreenController = new AboutDialogScreenController(this);
	progressBarScreenController = new ProgressBarScreenController(this);
	colorPickerScreenController = new ColorPickerScreenController(this);
	contextMenuScreenController = new ContextMenuScreenController(this);
	findReplaceDialogScreenController = new FindReplaceDialogScreenController(this);
	tooltipScreenController = new TooltipScreenController();
	draggingScreenController = new DraggingScreenController();
}

PopUps::~PopUps() {
	delete fileDialogScreenController;
	delete infoDialogScreenController;
	delete aboutDialogScreenController;
	delete progressBarScreenController;
	delete colorPickerScreenController;
	delete contextMenuScreenController;
	delete findReplaceDialogScreenController;
	delete tooltipScreenController;
	delete draggingScreenController;
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
	tooltipScreenController->initialize();
	draggingScreenController->initialize();
	Engine::getInstance()->getGUI()->addScreen(aboutDialogScreenController->getScreenNode()->getId(), aboutDialogScreenController->getScreenNode());
	Engine::getInstance()->getGUI()->addScreen(colorPickerScreenController->getScreenNode()->getId(), colorPickerScreenController->getScreenNode());
	Engine::getInstance()->getGUI()->addScreen(fileDialogScreenController->getScreenNode()->getId(), fileDialogScreenController->getScreenNode());
	Engine::getInstance()->getGUI()->addScreen(findReplaceDialogScreenController->getScreenNode()->getId(), findReplaceDialogScreenController->getScreenNode());
	Engine::getInstance()->getGUI()->addScreen(contextMenuScreenController->getScreenNode()->getId(), contextMenuScreenController->getScreenNode());
	Engine::getInstance()->getGUI()->addScreen(infoDialogScreenController->getScreenNode()->getId(), infoDialogScreenController->getScreenNode());
	Engine::getInstance()->getGUI()->addScreen(progressBarScreenController->getScreenNode()->getId(), progressBarScreenController->getScreenNode());
	Engine::getInstance()->getGUI()->addScreen(progressBarScreenController->getScreenNode()->getId(), progressBarScreenController->getScreenNode());
	Engine::getInstance()->getGUI()->addScreen(tooltipScreenController->getScreenNode()->getId(), tooltipScreenController->getScreenNode());
	Engine::getInstance()->getGUI()->addScreen(draggingScreenController->getScreenNode()->getId(), draggingScreenController->getScreenNode());
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
	Engine::getInstance()->getGUI()->removeScreen(tooltipScreenController->getScreenNode()->getId());
	Engine::getInstance()->getGUI()->removeScreen(draggingScreenController->getScreenNode()->getId());
	fileDialogScreenController->dispose();
	infoDialogScreenController->dispose();
	aboutDialogScreenController->dispose();
	progressBarScreenController->dispose();
	colorPickerScreenController->dispose();
	contextMenuScreenController->dispose();
	findReplaceDialogScreenController->dispose();
	tooltipScreenController->dispose();
	draggingScreenController->dispose();
}
