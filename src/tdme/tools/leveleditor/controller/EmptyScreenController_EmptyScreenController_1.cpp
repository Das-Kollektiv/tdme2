#include <tdme/tools/leveleditor/controller/EmptyScreenController_EmptyScreenController_1.h>

#include <tdme/tools/leveleditor/TDMELevelEditor.h>
#include <tdme/tools/leveleditor/controller/EmptyScreenController.h>
#include <tdme/tools/leveleditor/controller/LevelEditorEntityLibraryScreenController.h>
#include <tdme/tools/leveleditor/views/EmptyView.h>

using tdme::tools::leveleditor::controller::EmptyScreenController_EmptyScreenController_1;
using tdme::tools::leveleditor::TDMELevelEditor;
using tdme::tools::leveleditor::controller::EmptyScreenController;
using tdme::tools::leveleditor::controller::LevelEditorEntityLibraryScreenController;
using tdme::tools::leveleditor::views::EmptyView;

EmptyScreenController_EmptyScreenController_1::EmptyScreenController_EmptyScreenController_1(EmptyScreenController* emptyScreenController, EmptyView* finalView)
	: emptyScreenController(emptyScreenController)
	, finalView(finalView)
{
}

void EmptyScreenController_EmptyScreenController_1::performAction()
{
	finalView->updateGUIElements();
	TDMELevelEditor::getInstance()->getLevelEditorEntityLibraryScreenController()->setEntityLibrary();
}

