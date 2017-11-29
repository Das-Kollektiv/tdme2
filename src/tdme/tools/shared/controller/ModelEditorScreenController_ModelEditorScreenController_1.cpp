#include <tdme/tools/shared/controller/ModelEditorScreenController_ModelEditorScreenController_1.h>

#include <tdme/tools/shared/controller/ModelEditorScreenController.h>
#include <tdme/tools/shared/views/SharedModelEditorView.h>

using tdme::tools::shared::controller::ModelEditorScreenController_ModelEditorScreenController_1;
using tdme::tools::shared::controller::ModelEditorScreenController;
using tdme::tools::shared::views::SharedModelEditorView;

ModelEditorScreenController_ModelEditorScreenController_1::ModelEditorScreenController_ModelEditorScreenController_1(ModelEditorScreenController* modelEditorScreenController, SharedModelEditorView* finalView)
	: modelEditorScreenController(modelEditorScreenController)
	, finalView(finalView)
{
}

void ModelEditorScreenController_ModelEditorScreenController_1::performAction()
{
	finalView->updateGUIElements();
	finalView->onSetEntityData();
}
