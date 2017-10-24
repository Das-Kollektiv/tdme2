#include <tdme/tools/shared/views/PopUps.h>

#include <tdme/engine/Engine.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/tools/shared/controller/FileDialogScreenController.h>
#include <tdme/tools/shared/controller/InfoDialogScreenController.h>

using tdme::tools::shared::views::PopUps;
using tdme::engine::Engine;
using tdme::gui::GUI;
using tdme::gui::nodes::GUIScreenNode;
using tdme::tools::shared::controller::FileDialogScreenController;
using tdme::tools::shared::controller::InfoDialogScreenController;

PopUps::PopUps() 
{
}

PopUps::~PopUps() {
	delete fileDialogScreenController;
	delete infoDialogScreenController;
}

FileDialogScreenController* PopUps::getFileDialogScreenController()
{
	return fileDialogScreenController;
}

InfoDialogScreenController* PopUps::getInfoDialogScreenController()
{
	return infoDialogScreenController;
}

void PopUps::initialize()
{
	fileDialogScreenController = new FileDialogScreenController();
	fileDialogScreenController->initialize();
	infoDialogScreenController = new InfoDialogScreenController();
	infoDialogScreenController->initialize();
	Engine::getInstance()->getGUI()->addScreen(fileDialogScreenController->getScreenNode()->getId(), fileDialogScreenController->getScreenNode());
	Engine::getInstance()->getGUI()->addScreen(infoDialogScreenController->getScreenNode()->getId(), infoDialogScreenController->getScreenNode());
}

void PopUps::dispose()
{
	fileDialogScreenController->dispose();
	infoDialogScreenController->dispose();
}
