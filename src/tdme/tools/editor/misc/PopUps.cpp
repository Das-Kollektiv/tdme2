#include <tdme/tools/editor/misc/PopUps.h>

#include <memory>

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
#include <tdme/tools/editor/controllers/ImportDialogScreenController.h>
#include <tdme/tools/editor/controllers/InfoDialogScreenController.h>
#include <tdme/tools/editor/controllers/InputDialogScreenController.h>
#include <tdme/tools/editor/controllers/ProgressBarScreenController.h>
#include <tdme/tools/editor/controllers/SelectorDialogScreenController.h>
#include <tdme/tools/editor/controllers/TooltipScreenController.h>

using std::make_unique;
using std::unique_ptr;

using tdme::engine::Engine;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUI;
using tdme::tools::editor::controllers::AboutDialogScreenController;
using tdme::tools::editor::controllers::ColorPickerScreenController;
using tdme::tools::editor::controllers::ContextMenuScreenController;
using tdme::tools::editor::controllers::DraggingScreenController;
using tdme::tools::editor::controllers::FileDialogScreenController;
using tdme::tools::editor::controllers::FindReplaceDialogScreenController;
using tdme::tools::editor::controllers::ImportDialogScreenController;
using tdme::tools::editor::controllers::InputDialogScreenController;
using tdme::tools::editor::controllers::InfoDialogScreenController;
using tdme::tools::editor::controllers::ProgressBarScreenController;
using tdme::tools::editor::controllers::SelectorDialogScreenController;
using tdme::tools::editor::controllers::TooltipScreenController;
using tdme::tools::editor::misc::PopUps;

PopUps::PopUps()
{
	fileDialogScreenController = make_unique<FileDialogScreenController>(this);
	findReplaceDialogScreenController = make_unique<FindReplaceDialogScreenController>(this);
	inputDialogScreenController = make_unique<InputDialogScreenController>(this);
	infoDialogScreenController = make_unique<InfoDialogScreenController>(this);
	aboutDialogScreenController = make_unique<AboutDialogScreenController>(this);
	progressBarScreenController = make_unique<ProgressBarScreenController>(this);
	colorPickerScreenController = make_unique<ColorPickerScreenController>(this);
	importDialogScreenController = make_unique<ImportDialogScreenController>(this);
	selectorDialogScreenController = make_unique<SelectorDialogScreenController>(this);
	contextMenuScreenController = make_unique<ContextMenuScreenController>(this);
	tooltipScreenController = make_unique<TooltipScreenController>();
	draggingScreenController = make_unique<DraggingScreenController>();
}

PopUps::~PopUps() {
}

void PopUps::initialize()
{
	fileDialogScreenController->initialize();
	findReplaceDialogScreenController->initialize();
	inputDialogScreenController->initialize();
	infoDialogScreenController->initialize();
	aboutDialogScreenController->initialize();
	progressBarScreenController->initialize();
	colorPickerScreenController->initialize();
	importDialogScreenController->initialize();
	selectorDialogScreenController->initialize();
	contextMenuScreenController->initialize();
	tooltipScreenController->initialize();
	draggingScreenController->initialize();
	Engine::getInstance()->getGUI()->addScreen(aboutDialogScreenController->getScreenNode()->getId(), aboutDialogScreenController->getScreenNode());
	Engine::getInstance()->getGUI()->addScreen(importDialogScreenController->getScreenNode()->getId(), importDialogScreenController->getScreenNode());
	Engine::getInstance()->getGUI()->addScreen(colorPickerScreenController->getScreenNode()->getId(), colorPickerScreenController->getScreenNode());
	Engine::getInstance()->getGUI()->addScreen(fileDialogScreenController->getScreenNode()->getId(), fileDialogScreenController->getScreenNode());
	Engine::getInstance()->getGUI()->addScreen(findReplaceDialogScreenController->getScreenNode()->getId(), findReplaceDialogScreenController->getScreenNode());
	Engine::getInstance()->getGUI()->addScreen(inputDialogScreenController->getScreenNode()->getId(), inputDialogScreenController->getScreenNode());
	Engine::getInstance()->getGUI()->addScreen(selectorDialogScreenController->getScreenNode()->getId(), selectorDialogScreenController->getScreenNode());
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
	Engine::getInstance()->getGUI()->removeScreen(importDialogScreenController->getScreenNode()->getId());
	Engine::getInstance()->getGUI()->removeScreen(colorPickerScreenController->getScreenNode()->getId());
	Engine::getInstance()->getGUI()->removeScreen(fileDialogScreenController->getScreenNode()->getId());
	Engine::getInstance()->getGUI()->removeScreen(findReplaceDialogScreenController->getScreenNode()->getId());
	Engine::getInstance()->getGUI()->removeScreen(inputDialogScreenController->getScreenNode()->getId());
	Engine::getInstance()->getGUI()->removeScreen(selectorDialogScreenController->getScreenNode()->getId());
	Engine::getInstance()->getGUI()->removeScreen(contextMenuScreenController->getScreenNode()->getId());
	Engine::getInstance()->getGUI()->removeScreen(infoDialogScreenController->getScreenNode()->getId());
	Engine::getInstance()->getGUI()->removeScreen(progressBarScreenController->getScreenNode()->getId());
	Engine::getInstance()->getGUI()->removeScreen(tooltipScreenController->getScreenNode()->getId());
	Engine::getInstance()->getGUI()->removeScreen(draggingScreenController->getScreenNode()->getId());
	fileDialogScreenController->dispose();
	findReplaceDialogScreenController->dispose();
	inputDialogScreenController->dispose();
	infoDialogScreenController->dispose();
	aboutDialogScreenController->dispose();
	progressBarScreenController->dispose();
	colorPickerScreenController->dispose();
	importDialogScreenController->dispose();
	selectorDialogScreenController->dispose();
	contextMenuScreenController->dispose();
	tooltipScreenController->dispose();
	draggingScreenController->dispose();
}
