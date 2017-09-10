#include <tdme/tools/leveleditor/controller/TriggerScreenController_TriggerScreenController_1.h>

#include <tdme/tools/leveleditor/TDMELevelEditor.h>
#include <tdme/tools/leveleditor/controller/LevelEditorEntityLibraryScreenController.h>
#include <tdme/tools/leveleditor/controller/TriggerScreenController.h>
#include <tdme/tools/leveleditor/views/TriggerView.h>

using tdme::tools::leveleditor::controller::TriggerScreenController_TriggerScreenController_1;
using tdme::tools::leveleditor::TDMELevelEditor;
using tdme::tools::leveleditor::controller::LevelEditorEntityLibraryScreenController;
using tdme::tools::leveleditor::controller::TriggerScreenController;
using tdme::tools::leveleditor::views::TriggerView;

TriggerScreenController_TriggerScreenController_1::TriggerScreenController_TriggerScreenController_1(TriggerScreenController* triggerScreenController, TriggerView* finalView)
	: triggerScreenController(triggerScreenController)
	, finalView(finalView)
{
}

void TriggerScreenController_TriggerScreenController_1::performAction()
{
	finalView->updateGUIElements();
	TDMELevelEditor::getInstance()->getLevelEditorEntityLibraryScreenController()->setEntityLibrary();
}
