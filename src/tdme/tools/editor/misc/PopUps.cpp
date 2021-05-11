#include <tdme/tools/editor/misc/PopUps.h>

#include <tdme/engine/Engine.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/tools/editor/controllers/ColorPickerScreenController.h>
#include <tdme/tools/editor/controllers/FileDialogScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/controllers/ProgressBarScreenController.h>

using tdme::engine::Engine;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUI;
using tdme::tools::editor::controllers::ColorPickerScreenController;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::controllers::ProgressBarScreenController;
using tdme::tools::editor::misc::PopUps;

PopUps::PopUps()
{
	fileDialogScreenController = new FileDialogScreenController();
	infoDialogScreenController = new InfoDialogScreenController();
	progressBarScreenController = new ProgressBarScreenController();
	colorPickerScreenController = new ColorPickerScreenController();
}

PopUps::~PopUps() {
	delete fileDialogScreenController;
	delete infoDialogScreenController;
	delete progressBarScreenController;
	delete colorPickerScreenController;
}

FileDialogScreenController* PopUps::getFileDialogScreenController()
{
	return fileDialogScreenController;
}

InfoDialogScreenController* PopUps::getInfoDialogScreenController()
{
	return infoDialogScreenController;
}

ProgressBarScreenController* PopUps::getProgressBarScreenController()
{
	return progressBarScreenController;
}

ColorPickerScreenController* PopUps::getColorPickerScreenController()
{
	return colorPickerScreenController;
}


void PopUps::initialize()
{
	fileDialogScreenController->initialize();
	infoDialogScreenController->initialize();
	progressBarScreenController->initialize();
	colorPickerScreenController->initialize();
	Engine::getInstance()->getGUI()->addScreen(fileDialogScreenController->getScreenNode()->getId(), fileDialogScreenController->getScreenNode());
	Engine::getInstance()->getGUI()->addScreen(infoDialogScreenController->getScreenNode()->getId(), infoDialogScreenController->getScreenNode());
	Engine::getInstance()->getGUI()->addScreen(progressBarScreenController->getScreenNode()->getId(), progressBarScreenController->getScreenNode());
	Engine::getInstance()->getGUI()->addScreen(colorPickerScreenController->getScreenNode()->getId(), colorPickerScreenController->getScreenNode());
}

void PopUps::dispose()
{
	Engine::getInstance()->getGUI()->removeScreen(fileDialogScreenController->getScreenNode()->getId());
	Engine::getInstance()->getGUI()->removeScreen(infoDialogScreenController->getScreenNode()->getId());
	Engine::getInstance()->getGUI()->removeScreen(progressBarScreenController->getScreenNode()->getId());
	Engine::getInstance()->getGUI()->removeScreen(colorPickerScreenController->getScreenNode()->getId());
	fileDialogScreenController->dispose();
	infoDialogScreenController->dispose();
	progressBarScreenController->dispose();
	colorPickerScreenController->dispose();
}
